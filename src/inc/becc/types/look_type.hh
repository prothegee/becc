#ifndef BECC_LOOK_TYPE_HH
#define BECC_LOOK_TYPE_HH
#include "../becc.hh"

namespace becc
{

struct TLookAndReplace
{
    std::string to_look;
    std::string to_replace;
};
using look_and_replace_t = TLookAndReplace;

} // namespace becc

#endif // BECC_LOOK_TYPE_HH
