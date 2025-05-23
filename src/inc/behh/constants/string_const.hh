#ifndef BEHH_STRING_CONST_HH
#define BEHH_STRING_CONST_HH
#include "../pch.hh"

namespace behh {

// ABCDEFGHIJKLMNOPQRSTUVWXYZ
// abcdefghijklmnopqrstuvwxyz
// 0123456789+/
INLNSTTCCNST std::string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// 0123456789
INLNSTTCCNST std::string NUMERIC = "0123456789";

// ABCDEFGHIJKLMNOPQRSTUVWXYZ
// abcdefghijklmnopqrstuvwxyz
INLNSTTCCNST std::string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

// ABCDEFGHIJKLMNOPQRSTUVWXYZ
// abcdefghijklmnopqrstuvwxyz
// 0123456789
INLNSTTCCNST std::string ALPHANUMERIC = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/* ~!@#$%^&*()_+{}|:\"<>?`-=[]';,./\\ */ // using "//" will make code below seems like a comment
INLNSTTCCNST std::string SPECIAL_CHARACTER = "~!@#$%^&*()_+{}|:\"<>?`-=[]';,./\\";

// abcdefghijklmnopqrstuvwxyz
// ABCDEFGHIJKLMNOPQRSTUVWXYZ
// 0123456789
// ~!@#$%^&*-_=+
INLNSTTCCNST std::string ALPHANUMERIC_WITH_SPECIAL_CHARACTER = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789~!@#$%^&*-_=+";

// ABCDEFGHIJKLMNOPQRSTUVWXYZ
// 0123456789
INLNSTTCCNST std::string BASE36_DIGITS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// ABCDEFGHIJKLMNOPQRSTUVWXYZ
// 0123456789
INLNSTTCCNST char HEX_DIGITS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

} // namespace behh

#endif // BEHH_STRING_CONST_HH
