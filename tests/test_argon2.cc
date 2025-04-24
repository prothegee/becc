#include <becc/functions/cryptography.hh>
#include <iostream>
// #include <cassert>

int main()
{
    std::string password = "strong123!", salt = "abcdefghijklmnop", result;

    auto status = becc::cryptography_functions::hash::argon2id(password, salt, result);

    // can't do assert
    if (status != ARGON2_OK)
    {
        std::cerr << "fail to encode hashed result\n";
        return ARGON2_ENCODING_FAIL;
    }
    std::cout << "passed: argon2id as " << result << "\n";
    
    if (argon2id_verify(result.c_str(), password.data(), password.length()) != ARGON2_OK)
    {
        std::cerr << "fail to decode hashed result\n";
        return ARGON2_DECODING_FAIL;
    }
    std::cout << "passed: verified\n";

    return 0;
}