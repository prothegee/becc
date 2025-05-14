#include <becc/interfaces/icouchbase_core_interface.hh>

namespace becc {
#if BECC_USING_COUCHBASE_CXX_CLIENT
ICouchbaseCoreInterface::_ICouchbase::~_ICouchbase() {
    // nothing to free
}
#endif // BECC_USING_COUCHBASE_CXX_CLIENT
} // namespace becc
