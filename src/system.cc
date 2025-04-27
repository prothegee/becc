#include <becc/functions/system.hh>

namespace becc
{
namespace system_functions
{

int32_t is_port_available(const int32_t& port)
{
    int32_t sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
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
