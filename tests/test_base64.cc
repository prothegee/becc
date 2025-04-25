#include <becc/functions/utility.hh>
#include <iostream>
#include <cassert>

int main()
{
    std::string input = "encode me 123 !@#",  encode, encode_ssl, decode, decode_ssl;

    encode = becc::utility_functions::base64encode(input);
    decode = becc::utility_functions::base64decode(encode);

    assert(input == decode);
    std::cout << "passed: base64 encode & decode using stl ( without sanity check )\n";

    // no base64 sanity check

    #if BECC_USING_OPENSSL
    encode_ssl = becc::utility_functions::base64encode_openssl(input);
    decode_ssl = becc::utility_functions::base64decode_openssl(encode_ssl);

    assert(input == decode_ssl);
    std::cout << "passed: base64 encode & decode using openssl\n";

    // no base64 openssl sanity check
    #endif // BECC_USING_OPENSSL

    return 0;
}