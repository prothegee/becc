#include <becc/functions/cryptography.hh>

#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>

namespace becc
{
namespace cryptography_functions
{

namespace hash
{

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

    size_t encoded_len = argon2_encodedlen(
        computation,
        block,
        parallelism,
        salt.size(),
        derived_length,
        Argon2_id
    );

    std::vector<char> encoded_buffer(encoded_len);

    // Compute the full encoded string
    int32_t status = argon2id_hash_encoded(
        computation,        // Time cost
        block,        // Memory cost (KiB)
        parallelism,        // Parallelism
        input.data(),       // Input
        input.size(),       // Input length
        salt.data(),        // Salt
        salt.size(),        // Salt length
        derived_length,     // Output length
        encoded_buffer.data(), // Output buffer
        encoded_len         // Output buffer size
    );

    if (status != ARGON2_OK) {
        std::cerr << "hash::argon2id: encoding failed (code: " << status << ")\n";
        result.clear();
        return status;
    }

    result.assign(encoded_buffer.data(), encoded_len);

    return ARGON2_OK;
}

} // namespace hash

namespace stream_cipher
{
} // namespace stream_cipher

} // namespace cryptography_functions
} // namespace becc
