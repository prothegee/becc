#ifndef BEHH_AUTH_TYPE_HH
#define BEHH_AUTH_TYPE_HH

namespace behh {

/**
 * @brief auth basic type structure
 */
struct auth_basic_t {
    const char* username;
    const char* password;
};

} // namespace behh

#endif // BEHH_AUTH_TYPE_HH
