#ifndef BECC_LOOK_TYPE_HH
#define BECC_LOOK_TYPE_HH
#include <becc/becc.hh>

namespace becc {

/**
 * @brief look and replace type structure
 */
struct look_and_replace_t {
    std::string to_look;
    std::string to_replace;
};

} // namespace becc

#endif // BECC_LOOK_TYPE_HH
