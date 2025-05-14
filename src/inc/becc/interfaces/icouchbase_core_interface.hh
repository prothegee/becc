#ifndef BECC_ICOUCHBASE_CORE_INTERFACE_HH
#define BECC_ICOUCHBASE_CORE_INTERFACE_HH
#include <becc/becc.hh>

#if BECC_USING_COUCHBASE_CXX_CLIENT
#include <couchbase/cluster.hxx>
#include <couchbase/logger.hxx>
#include <couchbase/logger.hxx>
#include <couchbase/codec/tao_json_serializer.hxx>

namespace becc {

// reserved

////////////////////////////////////////////////

/**
 * @brief couchbase connection type structure
 */
struct couchbase_connection_t {
    std::string username;
    std::string password;
    std::string connection;
    std::string scope_name;
    std::string bucket_name;
    std::string collection_name;

    couchbase::cluster cluster_data;

    // reserved: multiple data center?
};

/**
 * @brief becc couchbase core interface structure
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

        std::string get_scope_name() { return ICouchbaseCoreInterface::m_connection.scope_name; }

        std::string get_bucket_name() { return ICouchbaseCoreInterface::m_connection.bucket_name; }

        std::string get_collection_name() { return ICouchbaseCoreInterface::m_connection.collection_name; }
    };
    // couchbase interface access
    _ICouchbase ICouchbase = _ICouchbase();

private:
    INLNSTTC couchbase_connection_t m_connection;
};

} // namespace becc
#endif // BECC_USING_COUCHBASE_CXX_CLIENT

#endif // BECC_ICOUCHBASE_CORE_INTERFACE_HH
