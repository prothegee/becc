#ifndef BECC_SYSTEM_HH
#define BECC_SYSTEM_HH
#include "../becc.hh"

#if _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

namespace becc
{
namespace system_functions
{

int32_t is_port_available(const int32_t& port);

} // namespace system_functions
} // namespace becc

#endif // BECC_SYSTEM_HH
