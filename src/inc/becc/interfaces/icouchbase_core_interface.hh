#ifndef BECC_ICOUCHBASE_CORE_INTERFACE_HH
#define BECC_ICOUCHBASE_CORE_INTERFACE_HH
#include <becc/becc.hh>

#if BECC_USING_COUCHBASE_CXX_CLIENT
#include <couchbase/cluster.hxx>
#include <couchbase/codec/tao_json_serializer.hxx>
#include <couchbase/logger.hxx>

#include <spdlog/fmt/bundled/core.h>

#include <couchbase/fmt/error.hxx>

namespace becc {

// reserved

////////////////////////////////////////////////

/**
 * @brief couchbase cluster constant profiles option/s
 * 
 * @note 1. wan_development
 */
struct couchbase_cluster_profiles {
    // currently only available "wan_development"?
    INLNSTTCCNST std::string wan_development = "wan_development";
};

/**
 * @brief couchbase connection type structure
 */
struct couchbase_connection_t {
    std::string host;
    std::string username;
    std::string password;
    std::string scope_name;
    std::string bucket_name;
    std::string collection_name;

    // reserved: multiple data center?
};

/**
 * @brief becc couchbase core interface structure
 *
 * @note this interface handle connection data while
 * @note child interface of ICouchbase is responsible to handle the cluster contact
 * @note if initialize_constructor return true or 1, you can get cluster data, collection data after that
 * 
 * @note this interface structure still useless
 */
struct ICouchbaseCoreInterface {
    virtual ~ICouchbaseCoreInterface() = default;

    // skipped: initialize_table

    /**
     * @brief initialize table index implementation
     *
     * @note prior 1
     */
    virtual void initialize_table_index() = 0;

    // skipped: initialize_table_materialized_view

    // skipped: initialize_table_and_alterize_table

    // couchbase interface structure
    struct _ICouchbase {
        virtual ~_ICouchbase();

        // print error?

        /**
         * @brief 
         * 
         * @note couchbase_log_level will not appear in release build
         * 
         * @param connection 
         * @param couchbase_log_level 0:trace 1:debug 2:info 3:warn 4:error 5:critical 6:off
         * @param extra_info 
         * @return int32_t 
         */
        int32_t initialize_constructor(const couchbase_connection_t& connection, const int32_t& couchbase_log_level = 6, const char* extra_info = "");

        std::string get_scope_name() { return ICouchbaseCoreInterface::m_connection.scope_name; }

        std::string get_bucket_name() { return ICouchbaseCoreInterface::m_connection.bucket_name; }

        std::string get_collection_name() { return ICouchbaseCoreInterface::m_connection.collection_name; }

        couchbase::cluster get_cluster() { return m_cluster.second; }

        couchbase::error get_cluster_error() { return m_cluster.first; }

        couchbase::collection get_collection() {
            return m_cluster.second.bucket(get_bucket_name())
                .scope(get_scope_name())
                .collection(get_collection_name());
        }
    private:
        // first: error data
        // second: cluster data
        std::pair<couchbase::error, couchbase::cluster> m_cluster;
    };
    // couchbase interface access
    _ICouchbase ICouchbase = _ICouchbase();

private:
    INLNSTTC couchbase_connection_t m_connection;
};

} // namespace becc
#endif // BECC_USING_COUCHBASE_CXX_CLIENT

#endif // BECC_ICOUCHBASE_CORE_INTERFACE_HH
