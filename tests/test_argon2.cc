#include <becc/functions/cryptography.hh>
#include <iostream>
#include <cassert>

int main()
{
#if BECC_USING_ARGON2
    std::string password = "strong123!", salt = "abcdefghijklmnop", result;

    auto status = becc::cryptography_functions::hash::argon2id(password, salt, result);

    assert(status == (int32_t)ARGON2_OK);
    std::cout << "passed: argon2id as " << result << "\n";
 
    auto verify = argon2id_verify(result.c_str(), password.data(), password.length());
    assert(verify == ARGON2_OK);
    std::cout << "passed: argon2id verified\n";
#endif // BECC_USING_ARGON2
    return 1;
}