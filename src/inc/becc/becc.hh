#ifndef BECC_HH
#define BECC_HH
#include "config.hh"
#include "export.hh"

#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include <sstream>

namespace becc
{
} // namespace becc

// alias for float as in 32 bits
using float32_t = float;

// alias for double as in 64 bits
using float64_t = double;

/// no int128_t & float128_t, for now

// alias for std::vector<unsigned char> as buffer type
using buffer_t = std::vector<unsigned char>;

// alias for unsigned char
using uchr_t = unsigned char;

////////////////////////////////////////////////////////////////////////

#endif // BECC_HH
