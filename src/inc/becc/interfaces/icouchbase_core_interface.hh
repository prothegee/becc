#ifndef BECC_ICOUCHBASE_CORE_INTERFACE_HH
#define BECC_ICOUCHBASE_CORE_INTERFACE_HH
#include <becc/becc.hh>

namespace becc {
#if BECC_USING_COUCHBASE_CXX_CLIENT
#endif // BECC_USING_COUCHBASE_CXX_CLIENT

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
        // 
    };
    // couchbase interface access
    _ICouchbase ICouchbase = _ICouchbase();
};

} // namespace becc

#endif // BECC_ICOUCHBASE_CORE_INTERFACE_HH
