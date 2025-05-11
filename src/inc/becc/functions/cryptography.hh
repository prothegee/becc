#ifndef BECC_CRYPTOGRAPHY_HH
#define BECC_CRYPTOGRAPHY_HH
#include <becc/becc.hh>

#if BECC_USING_OPENSSL
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#endif // BECC_USING_OPENSSL

#if BECC_USING_ARGON2
#include <argon2.h>
#endif // BECC_USING_ARGON2

namespace becc {
namespace cryptography_functions {

#if BECC_USING_OPENSSL
/**
 * @brief regenerate data to hex string
 *
 * @param data
 * @param length
 * @return std::string
 */
std::string bytes_to_hex_openssl(const unsigned char* data, size_t length);

/**
 * @brief regenerate string data to hex string
 *
 * @param input
 * @return std::string
 */
std::string string_to_hex_string_openssl(const std::string& input);

/**
 * @brief get result to custom base 36 with openssl lib
 *
 * @param input
 * @return std::string
 */
std::string string_to_custom_base36_openssl(const std::string& input);

/**
 * @brief get result from custom base 36 with openssl lib
 *
 * @param input
 * @return std::string
 */
std::string string_from_custom_base36_openssl(const std::string& input);
#endif // LIBPRCPP_USING_OPENSSL

namespace hash {

#if BECC_USING_OPENSSL
/**
 * @brief generate sha1
 *
 * @note return length is 40
 *
 * @param input
 * @return std::string
 */
std::string sha1_openssl(const std::string& input);

/**
 * @brief generate sha224
 *
 * @note return length is 56
 *
 * @param input
 * @return std::string
 */
std::string sha224_openssl(const std::string& input);

/**
 * @brief generate sha1
 *
 * @note return length is 64
 *
 * @param input
 * @return std::string
 */
std::string sha256_openssl(const std::string& input);

/**
 * @brief generate sha1
 *
 * @note return length is 96
 *
 * @param input
 * @return std::string
 */
std::string sha384_openssl(const std::string& input);

/**
 * @brief generate sha1
 *
 * @note return length is 128
 *
 * @param input
 * @return std::string
 */
std::string sha512_openssl(const std::string& input);
#endif // BECC_USING_OPENSSL

#if BECC_USING_ARGON2
/**
 * @brief hash using argon2id
 *
 * @note this function is password hashing
 *
 * @param input raw input data
 * @param salt required at least 16 length
 * @param result result string to stored
 * @param computation pass computation cost
 * @param block block size of memory cost KiB
 * @param parallelism thread usage cost
 * @param derived_length derive length
 * @return int32_t 1 mean ok
 */
int32_t argon2id(const std::string& input, const std::string& salt, std::string& result, const uint32_t& computation = 2, const uint32_t& block = 1 << 21, const uint32_t& parallelism = 1, const uint32_t& derived_length = 32);

/**
 * @brief argon2id hash verifier
 *
 * @param input raw input
 * @param hash_encoded hash encoded
 * @return int32_t 1 mean ok
 */
int32_t argon2id_verifier(const std::string& input, const std::string& hash_encoded);
#endif // BECC_USING_ARGON2

} // namespace hash

namespace stream_cipher {

#if BECC_USING_OPENSSL
/**
 * @brief aes cbc encrypt input
 *
 * @param input data/message
 * @param output output to store the result
 * @param iv recomended length is 16
 * @param ik recomended length is 32
 * @return int32_t 1 mean ok
 */
int32_t aes_cbc_encrypt_openssl(const std::string& input, std::string& output, const std::string& iv, const std::string& ik);

/**
 * @brief aes cbc decrypt
 *
 * @param input
 * @param output
 * @param iv
 * @param ik
 * @return int32_t 1 mean ok
 */
int32_t aes_cbc_decrypt_openssl(const std::string& input, std::string& output, const std::string& iv, const std::string& ik);

/**
 * @brief aes cbc encrypt buffer
 *
 * @param buffer
 * @param iv_buffer
 * @param ik_buffer
 * @return buffer_t
 */
buffer_t aes_cbc_encrypt_to_buffer_openssl(const buffer_t& buffer, uchr_t* iv_buffer, uchr_t* ik_buffer);

/**
 * @brief aes cbc decrypt buffer
 *
 * @param buffer
 * @param iv_buffer
 * @param ik_buffer
 * @return buffer_t
 */
buffer_t aes_cbc_decrypt_to_buffer_openssl(const buffer_t& buffer, uchr_t* iv_buffer, uchr_t* ik_buffer);
#endif // BECC_USING_OPENSSL

} // namespace stream_cipher

} // namespace cryptography_functions
} // namespace becc

#endif // BECC_CRYPTOGRAPHY_HH