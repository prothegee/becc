#include <becc/functions/utility.hh>
#include <iostream>
#include <cassert>

int main()
{
    std::string input = "encode me 123 !@#",  encode, encode_ssl, decode, decode_ssl;

    encode = becc::utility_functions::base64encode(input);
    decode = becc::utility_functions::base64decode(encode);

    assert(input != decode && "input & final decode is not match! using stl");
    std::cout << "passed: base64 encode & decode using stl\n";

    #if BECC_USING_OPENSSL
    encode_ssl = becc::utility_functions::base64encode_openssl(input);
    decode_ssl = becc::utility_functions::base64decode_openssl(encode_ssl);

    assert(input != decode && "input & final decode is not match! using openssl");
    std::cout << "passed: base64 encode & decode using openssl\n";
    #endif // BECC_USING_OPENSSL

    return 0;
}