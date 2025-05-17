#include <behh/functions/utility.hh>
#include <cassert>
#include <iostream>

int main() {
    std::string input = "encode me 123 !@#", encode, encode_ssl, decode, decode_ssl;

    encode = behh::utility_functions::base64encode(input);
    decode = behh::utility_functions::base64decode(encode);

    assert(input == decode);
    std::cout << "passed: base64 encode & decode using stl\n";

    // no base64 sanity check

    //////////////////////////////////////////////////////////////////

#if BEHH_USING_OPENSSL
    encode_ssl = behh::utility_functions::base64encode_openssl(input);
    decode_ssl = behh::utility_functions::base64decode_openssl(encode_ssl);

    assert(input == decode_ssl);
    std::cout << "passed: base64 encode & decode using openssl\n";

// no base64 openssl sanity check
#endif // BEHH_USING_OPENSSL

    return 0;
}