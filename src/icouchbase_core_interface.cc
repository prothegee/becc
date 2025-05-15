#include <becc/interfaces/icouchbase_core_interface.hh>

#include <couchbase/management/bucket_settings.hxx>

#include <iostream>
#include <utility>

namespace becc {
#if BECC_USING_COUCHBASE_CXX_CLIENT
ICouchbaseCoreInterface::~ICouchbaseCoreInterface() {
}

ICouchbaseCoreInterface::_ICouchbase::~_ICouchbase() {
    m_cluster.close().get();
}

void ICouchbaseCoreInterface::_ICouchbase::print_error(couchbase::error& error, const std::string& info) {
    // 
    (info.empty())
        ? std::cerr << "ERROR: " << fmt::format("{}", error) << "\n- error info is not provided\n"
        : std::cerr << "ERROR: " << fmt::format("{}", error) << "\n- error info: " <<  info << "\n";
}

int32_t ICouchbaseCoreInterface::_ICouchbase::initialize_constructor(const couchbase_connection_t& connection, const int32_t& couchbase_log_level, const char* extra_info) {
#if BECC_IS_DEBUG
    if (couchbase_log_level > -1 || couchbase_log_level < 7) {
        couchbase::logger::initialize_console_logger();
        couchbase::logger::set_level((couchbase::logger::log_level)couchbase_log_level);
    }
#endif // BECC_IS_DEBUG

#if BECC_IS_DEBUG
    if (connection.host.empty()) {
        std::cout << "DEBUG: warning, connection.host is empty\n";
    }
    if (connection.username.empty()) {
        std::cout << "DEBUG: warning, connection.username is empty\n";
    }
    if (connection.password.empty()) {
        std::cout << "DEBUG: warning, connection.password is empty\n";
    }

    if (connection.scope_name.empty()) {
        std::cout << "DEBUG: warning, connection.scope_name is empty\n";
    }
    if (connection.bucket_name.empty()) {
        std::cout << "DEBUG: warning, connection.bucket_name is empty\n";
    }
    if (connection.collection_name.empty()) {
        std::cout << "DEBUG: warning, connection.collection_name is empty\n";
    }
#else
    // this is release
    // make it all error
    if (connection.host.empty()) {
        std::cerr << "ERROR: connection.host can't empty\n";
        return -1;
    }
    if (connection.username.empty()) {
        std::cerr << "ERROR: connection.username can't empty\n";
        return -2;
    }
    if (connection.password.empty()) {
        std::cerr << "ERROR: connection.password can't empty\n";
        return -3;
    }

    if (connection.scope_name.empty()) {
        std::cerr << "ERROR: connection.scope_name can't empty\n";
        return -4;
    }
    if (connection.bucket_name.empty()) {
        std::cerr << "ERROR: connection.bucket_name can't empty\n";
        return -5;
    }
    if (connection.collection_name.empty()) {
        std::cerr << "ERROR: connection.collection_name can't empty\n";
        return -7;
    }
#endif // BECC_IS_DEBUG

    // member data assign
    {
        ICouchbaseCoreInterface::m_connection.host = connection.host;
        ICouchbaseCoreInterface::m_connection.username = connection.username;
        ICouchbaseCoreInterface::m_connection.password = connection.password;
        ICouchbaseCoreInterface::m_connection.scope_name = connection.scope_name;
        ICouchbaseCoreInterface::m_connection.bucket_name = connection.bucket_name;
        ICouchbaseCoreInterface::m_connection.collection_name = connection.collection_name;
    }

    couchbase::cluster_options option = couchbase::cluster_options(connection.username, connection.password);

    option.apply_profile(couchbase_cluster_profiles::wan_development);

    auto&& connection_result = couchbase::cluster::connect(connection.host, option).get();

    if (connection_result.first) {
#if BECC_IS_DEBUG
    (std::strlen(extra_info) > 0)
        ? std::cerr << "DEBUG: \"ICouchbaseCoreInterface::_ICouchbase::initialize_constructor\" fail to connect: \"" << extra_info << "\" | error code: " << connection_result.first.ec().message() << "\n"
        : std::cerr << "DEBUG: \"ICouchbaseCoreInterface::_ICouchbase::initialize_constructor\" fail to connect: ( extra_info is not provided )\n";
#endif // BECC_IS_DEBUG
        return -9;
    }

    m_current_bucket_exists = 0; // false
    m_current_bucket_scope_exists = 0; // false
    m_current_bucket_scope_collection_exists = 0; // false

    // move connection_result where connection_result can't be used again
    m_cluster = std::forward<couchbase::cluster>(connection_result.second);
    m_cluster_error = std::forward<couchbase::error>(connection_result.first);

    auto bucket_manager = m_cluster.buckets();

    auto buckets = bucket_manager.get_all_buckets().get();
    auto all_buckets = buckets.second;

    const int8_t MAX_BUCKET_SIZE_WARN = 3;
    // check all buckets size
    if (all_buckets.size() >= MAX_BUCKET_SIZE_WARN) {
        std::cout << "NOTE: the bucket size/list is " << all_buckets.size() << ", since it's grater or equal than " << MAX_BUCKET_SIZE_WARN << "\n";
    }

    for (auto& bucket : all_buckets) {
        if (bucket.name == connection.bucket_name) {
            m_current_bucket_exists = 1; // true
            break;
        }
    }

    if (!m_current_bucket_exists) {
        try {
            couchbase::management::cluster::bucket_settings settings;

            // in debug it's empty, but in release it shouldn't reach here
            if (connection.bucket_name.empty()) {
        #if BECC_IS_DEBUG
                std::cout << "WARNING: this seems a debug and bucket name is empty, set to \"bucket_default\"\n";

                settings.name = "bucket_default";
        #else
                std::cerr << "ERROR: it's release build, but bucket name is still empty somehow\n";
                exit(555666);
        #endif // BECC_IS_DEBUG
            } else {
                settings.name = connection.bucket_name;
            }

            bucket_manager.create_bucket(settings).get();
        } catch (const std::exception& e) {
            std::cerr << "FATAL: can't create \"" << connection.bucket_name << "\" bucket: " << e.what() << "\n";
            return -69;
        }
    }

    PRAGMA_MESSAGE("TODO?: restart if exists and con config apply reinit?")

    auto bucket = m_cluster.bucket(connection.bucket_name);

    auto collection_manager = bucket.collections();
    auto all_scopes = collection_manager.get_all_scopes().get();

    // check current scope & collection
    for (auto& scope : all_scopes.second) {
        if (scope.name == connection.scope_name) {
            m_current_bucket_scope_exists = 1; // true

            for (auto& collection : scope.collections) {
                if (collection.name == connection.collection_name) {
                    m_current_bucket_scope_collection_exists = 1; // true
                    break;
                }
            }
            break;
        }
    }

    // make faill if scope not exists? but it's okay if not valid
    // make faill if collection not exists? but it's okay if not valid & collection depend on object who controlled it when using this interface
    // just give note warning while in debug build
#if BECC_IS_DEBUG
    if (!m_current_bucket_scope_exists) {
        std::cout << "DEBUG: be warn, scope of \"" << connection.scope_name << "\" it might be new\n";
    }

    if (!m_current_bucket_scope_collection_exists) {
        std::cout << "DEBUG: be warn, colletion of \"" << connection.collection_name << "\" it might be new\n";
    }

    (std::strlen(extra_info) > 0)
        ? std::cout << "DEBUG: \"ICouchbaseCoreInterface::_ICouchbase::initialize_constructor\" connected: " << extra_info << "\"\n"
        : std::cout << "DEBUG: \"ICouchbaseCoreInterface::_ICouchbase::initialize_constructor\" connected: ( extra_info is not provided )\n";
#endif // BECC_IS_DEBUG

    return 1;
}
#endif // BECC_USING_COUCHBASE_CXX_CLIENT
} // namespace becc
