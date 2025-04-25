#include <becc/constants/string_const.hh>
#include <becc/functions/cryptography.hh>

#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>

namespace becc
{
namespace cryptography_functions
{

#if BECC_USING_OPENSSL
std::string bytes_to_hex_openssl(const unsigned char *data, size_t length)
{
    std::stringstream ss;

    for (size_t i = 0; i < length; ++i)
    {
        ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }

    return ss.str();
}

std::string string_to_hex_string_openssl(const std::string &input)
{
    std::string result;

    result.reserve(input.length() * 2);

    for (unsigned char byte : input)
    {
        result.push_back(HEX_DIGITS[byte >> 4]);
        result.push_back(HEX_DIGITS[byte & 0x1F]);
    }

    return result;
}

std::string string_to_custom_base36_openssl(const std::string &input)
{
    std::string result;

    unsigned int value = 0;
    int bits = 0;

    for (unsigned char byte : input)
    {
        value = (value << 8) | byte;
        bits += 8;

        while (bits >= 5)
        {
            bits -= 5;
            result.push_back(BASE36_DIGITS[(value >> bits) & 0x1F]); // mask for 5 bits (0x1F)
        }
    }

    if (bits > 0)
    {
        result.push_back(BASE36_DIGITS[(value << (5 - bits)) & 0x1F]);
    }

    return result;
}

std::string string_from_custom_base36_openssl(const std::string &input)
{
    std::string result;

    int bits = 0;
    unsigned int value = 0;
    bool loop_break = false;

    for (unsigned char c : input)
    {
        size_t index = BASE36_DIGITS.find(c);
        if (index == std::string::npos)
        {
            loop_break = true;
            std::cerr << "ERROR: Character '" << static_cast<int>(c) << "' not found in base62 character set.\n";
            break;
        }

        if (loop_break) { break; }

        value = (value << 5) | static_cast<unsigned int>(index);
        bits += 5;

        if (bits >= 8)
        {
            bits -= 8;
            result.push_back((value >> bits) & 0xFF); // mask for 8 bits (0xFF)
        }
    }

    return result;
}
#endif // BECC_USING_OPENSSL

namespace hash
{

#if BECC_USING_ARGON2
int32_t argon2id(const std::string& input, const std::string& salt, std::string& result, const uint32_t& computation, const uint32_t& block, const uint32_t& parallelism, const uint32_t& derived_length)
{
    if (input.length() < 6 || salt.length() < 1)
    {
        std::cerr << "hash::argon2id: input (min. 6 length) & salt (min. 16 length) required\n";
        return ARGON2_INCORRECT_PARAMETER;
    }

    if (input.empty() || salt.empty())
    {
        std::cerr << "hash::argon2id: input (min. 6 length) & salt (min. 16 length) required\n";
        return ARGON2_INCORRECT_PARAMETER;
    }

    // encoded length value
    size_t encoded_len = argon2_encodedlen(
        computation,
        block,
        parallelism,
        salt.size(),
        derived_length,
        Argon2_id
    );
    std::vector<char> encoded_buffer(encoded_len);

    // encoded buffer value
    int32_t status = argon2id_hash_encoded(
        computation,
        block,
        parallelism,
        input.data(),
        input.size(),
        salt.data(),
        salt.size(),
        derived_length,
        encoded_buffer.data(),
        encoded_len
    );

    if (status != ARGON2_OK) {
        std::cerr << "hash::argon2id: encoding failed (code: " << status << ")\n";
        result.clear();
        return status;
    }

    // pass to result storage
    result.assign(encoded_buffer.data(), encoded_len);

    return ARGON2_OK;
}

int32_t argon2id_verifier(const std::string& input, const std::string& hash_encoded)
{
    if (argon2id_verify(hash_encoded.c_str(), input.data(), input.length()) != ARGON2_OK)
    {
        return -1;
    }

    return 0;
}
#endif // BECC_USING_ARGON2

} // namespace hash

namespace stream_cipher
{

#if BECC_USING_OPENSSL
int32_t aes_cbc_encrypt_openssl(const std::string& input, std::string& output, const std::string& iv, const std::string& ik)
{
    EVP_CIPHER_CTX *pCtx = EVP_CIPHER_CTX_new();

    if (!pCtx)
    {
        std::cerr << "stream_cipher::aes_encrypt_openssl: fail to create cipher context!\n";
        return -1;
    }

    if (EVP_EncryptInit_ex(pCtx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char *>(ik.c_str()), reinterpret_cast<const unsigned char *>(iv.c_str())) != 1)
    {
        EVP_CIPHER_CTX_free(pCtx);
        std::cerr << "stream_cipher::aes_encrypt_openssl: fail to initialize cipher context!\n";
        return -2;
    }

    int32_t len = 0, ciphertex_len = 0;
    buffer_t ciphertext(input.size() + AES_BLOCK_SIZE);
    if (EVP_EncryptUpdate(pCtx, ciphertext.data(), &len, reinterpret_cast<const unsigned char *>(input.c_str()), (int)input.size()) != 1)
    {
        EVP_CIPHER_CTX_free(pCtx);
        std::cerr << "stream_cipher::aes_encrypt_openssl: fail to encrypt data context!\n";
        return -3;
    }
    ciphertex_len = len;

    if (EVP_EncryptFinal_ex(pCtx, ciphertext.data() + len, &len) != 1)
    {
        EVP_CIPHER_CTX_free(pCtx);
        std::cerr << "stream_cipher::aes_encrypt_openssl: fail to finalize data context!\n";
        return -4;
    }
    ciphertex_len += len;

    std::string tmp_out(ciphertext.begin(), ciphertext.begin() + ciphertex_len);

    output = string_to_custom_base36_openssl(tmp_out);

    EVP_CIPHER_CTX_free(pCtx); // start free object/s

    return 0;
}

int32_t aes_cbc_decrypt_openssl(const std::string& input, std::string& output, const std::string& iv, const std::string& ik)
{
    std::string binary_input = string_from_custom_base36_openssl(input);

    EVP_CIPHER_CTX *pCtx = EVP_CIPHER_CTX_new();

    if (!pCtx)
    {
        std::cerr << "stream_cipher::aes_cbc_decrypt_openssl: failed to create cipher context\n";
        return -1;
    }

    if (EVP_DecryptInit_ex(pCtx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char *>(ik.c_str()), reinterpret_cast<const unsigned char *>(iv.c_str())) != 1)
    {
        EVP_CIPHER_CTX_free(pCtx);
        std::cerr << "stream_cipher::aes_cbc_decrypt_openssl: fail to initialize cipher context!\n";
        return -2;
    }

    int32_t len = 0, plaintext_len = 0;
    buffer_t plaintext(binary_input.size() + AES_BLOCK_SIZE);
    if (EVP_DecryptUpdate(pCtx, plaintext.data(), &len, reinterpret_cast<const unsigned char *>(binary_input.c_str()), (int)binary_input.size()) != 1)
    {
        EVP_CIPHER_CTX_free(pCtx);
        std::cerr << "stream_cipher::aes_cbc_decrypt_openssl: fail to encrypt data context!\n";
        return -3;
    }
    plaintext_len = len;

    if (EVP_DecryptFinal_ex(pCtx, plaintext.data() + len, &len) != 1)
    {
        EVP_CIPHER_CTX_free(pCtx);
        std::cerr << "stream_cipher::aes_cbc_decrypt_openssl: fail to finalize data context!\n";
        return -4;
    }
    plaintext_len += len;
    
    output.assign(plaintext.begin(), plaintext.begin() + plaintext_len);

    EVP_CIPHER_CTX_free(pCtx);

    return 0;
}
#endif // BECC_USING_OPENSSL

} // namespace stream_cipher

} // namespace cryptography_functions
} // namespace becc
