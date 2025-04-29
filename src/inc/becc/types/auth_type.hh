#ifndef BECC_AUTH_TYPE_HH
#define BECC_AUTH_TYPE_HH

namespace becc
{

/**
 * @brief auth basic type structure
 */
struct auth_basic_t
{
    const char* username;
    const char* password;
};

} // namespace becc

#endif // BECC_AUTH_TYPE_HH
