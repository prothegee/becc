#ifndef BECC_STRING_CONST_HH
#define BECC_STRING_CONST_HH
#include "../becc.hh"

namespace becc
{

/*
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghijklmnopqrstuvwxyz
0123456789+/
*/
INLNSTTCCNST std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// 0123456789
INLNSTTCCNST std::string numeric = "0123456789";
/*
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghijklmnopqrstuvwxyz
*/
INLNSTTCCNST std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
/*
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghijklmnopqrstuvwxyz
0123456789
*/
INLNSTTCCNST std::string alphanumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
/*
~!@#$%^&*()_+{}|:\"<>?`-=[]';,./\\
*/
INLNSTTCCNST std::string special_character = "~!@#$%^&*()_+{}|:\"<>?`-=[]';,./\\";
/*
abcdefghijklmnopqrstuvwxyz
ABCDEFGHIJKLMNOPQRSTUVWXYZ
0123456789
~!@#$%^&*-_=+
*/
INLNSTTCCNST std::string alphanumeric_with_special_character = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789~!@#$%^&*-_=+";

/*
ABCDEFGHIJKLMNOPQRSTUVWXYZ
0123456789
*/
INLNSTTCCNST std::string BASE36_DIGITS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/*
ABCDEFGHIJKLMNOPQRSTUVWXYZ
0123456789
*/
INLNSTTCCNST char HEX_DIGITS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

} // namespace becc

#endif // BECC_STRING_CONST_HH
