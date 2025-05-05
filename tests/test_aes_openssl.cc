#include <becc/functions/cryptography.hh>
#include <iostream>
#include <cassert>

int main()
{
    std::string message = "this is our message", encrypted, decrypted;
    std::string iv = "2TpQjkQLRsj5Zxgc";
    std::string ik = "zu7yvTKAH8C5c2V6Ja7VBG4U7fNjjkGL";

    assert(becc::cryptography_functions::stream_cipher::aes_cbc_encrypt_openssl(message, encrypted, iv, ik) == 0);
    std::cout << "passed: encrypt aes openssl\n";

    assert(becc::cryptography_functions::stream_cipher::aes_cbc_decrypt_openssl(encrypted, decrypted, iv, ik) == 0);
    std::cout << "passed: decrypt aes openssl\n";

    assert(message == decrypted);
    std::cout << "passed: message is original\n";

    return 1;
}