#include <becc/interfaces/icouchbase_core_interface.hh>

#include <iostream>
#include <utility>

namespace becc {
#if BECC_USING_COUCHBASE_CXX_CLIENT
ICouchbaseCoreInterface::~ICouchbaseCoreInterface() {
    // 
    std::cout << "TMP: ~ICouchbaseCoreInterface()\n";
}

ICouchbaseCoreInterface::_ICouchbase::~_ICouchbase() {
    // 
    std::cout << "TMP: ~ICouchbaseCoreInterface()\n";
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

    // // fine
    // auto [error, cluster] = couchbase::cluster::connect(connection.host, option).get();

    // if (error) {
    //     std::cout << "error! " << error.ec().message() << "\n";
    // } else {
    //     std::cout << "continue!\n";
    // }
    // // fine

    // do not use this again if first is 
    auto&& connection_result = couchbase::cluster::connect(connection.host, option).get();

    if (connection_result.first) {
#if BECC_IS_DEBUG
    (std::strlen(extra_info) > 0)
        ? std::cerr << "DEBUG: \"ICouchbaseCoreInterface::_ICouchbase::initialize_constructor\" fail to connect: " << extra_info << "\"\n"
        : std::cerr << "DEBUG: \"ICouchbaseCoreInterface::_ICouchbase::initialize_constructor\" fail to connect: ( extra_info is not provided )\n";
#endif // BECC_IS_DEBUG
        return -9;
    }

    m_cluster = std::forward<couchbase::cluster>(connection_result.second);
    m_cluster_error = std::forward<couchbase::error>(connection_result.first);

#if BECC_IS_DEBUG
    (std::strlen(extra_info) > 0)
        ? std::cout << "DEBUG: \"ICouchbaseCoreInterface::_ICouchbase::initialize_constructor\" connected: " << extra_info << "\"\n"
        : std::cout << "DEBUG: \"ICouchbaseCoreInterface::_ICouchbase::initialize_constructor\" connected: ( extra_info is not provided )\n";
#endif // BECC_IS_DEBUG

    return 1;
}
#endif // BECC_USING_COUCHBASE_CXX_CLIENT
} // namespace becc
