#ifndef BECC_CRYPTOGRAPHY_HH
#define BECC_CRYPTOGRAPHY_HH
#include "../becc.hh"

#if BECC_USING_OPENSSL
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#endif // BECC_USING_OPENSSL

#if BECC_USING_ARGON2
#include <argon2.h>
#endif // BECC_USING_ARGON2

namespace becc
{
namespace cryptography_functions
{

namespace hash
{

/**
 * @brief hash using argon2id
 * 
 * @note this function is password hashing
 * 
 * @param input raw input data
 * @param salt required at least 16 length
 * @param result result string to stored
 * @param computation pass computation cost
 * @param block block size of memory cost
 * @param parallelism thread usage cost
 * @param derived_length derive length
 * @return int32_t 0 mean ok
 */
int32_t argon2id(const std::string& input, const std::string& salt, std::string& result, const uint32_t& computation = 2, const uint32_t& block = 1 << 21, const uint32_t& parallelism = 1, const uint32_t& derived_length = 32);

} // namespace hash

namespace stream_cipher
{
} // namespace stream_cipher

} // namespace cryptography_functions
} // namespace becc

#endif // BECC_CRYPTOGRAPHY_HH