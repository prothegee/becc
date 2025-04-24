#ifndef BECC_CONFIG_HH
#define BECC_CONFIG_HH

#define BECC_VERSION_MAJOR @BECC_VERSION_MAJOR@

#define BECC_VERSION_MINOR @BECC_VERSION_MINOR@

#define BECC_VERSION_PATCH @BECC_VERSION_PATCH@

#define BECC_VERSION_RELEASE_DATE @BECC_VERSION_RELEASE_DATE@

#define BECC_USING_VCPKG @BECC_USING_VCPKG@

#define BECC_USING_CURL @BECC_USING_CURL@
#define BECC_USING_CURL_EXECUTEABLE @BECC_USING_CURL_EXECUTEABLE@

#define BECC_USING_OPENSSL @BECC_USING_OPENSSL@

#define BECC_USING_JSONCPP @BECC_USING_JSONCPP@

#define BECC_USING_ARGON2 @BECC_USING_ARGON2@

#ifndef INLNSTTC
#define INLNSTTC inline static
#endif // INLNSTTC

#ifndef INLNSTTCCNST
#define INLNSTTCCNST inline static const
#endif // INLNSTTCCNST

#if defined(__GNUC__) || defined(__clang__)
    #define DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
    #define DEPRECATED(msg) __declspec(deprecated(msg))
#else
    #define DEPRECATED(msg)
#endif

#endif // BECC_CONFIG_HH
