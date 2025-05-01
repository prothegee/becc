#include <becc/functions/system.hh>

namespace becc
{
namespace system_functions
{

int32_t is_port_available(const int32_t& port)
{
    #if WIN32
    int32_t sock = (int32_t)socket(AF_INET, SOCK_STREAM, 0);
    #else
    int32_t sock = socket(AF_INET, SOCK_STREAM, 0);
    #endif
    if (sock < 0) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    #if WIN32
    addr.sin_port = htons(static_cast<u_short>(port));
    #else
    addr.sin_port = htons(port);
    #endif // WIN32 
    addr.sin_addr.s_addr = INADDR_ANY;

    bool available = (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0);
    #ifdef _WIN32
    closesocket(sock);
    #else
    close(sock);
    #endif
    return available;
}

} // namespace system_functions
} // namespace becc
