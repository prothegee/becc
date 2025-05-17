#ifndef BEHH_SYSTEM_HH
#define BEHH_SYSTEM_HH
#include "../pch.hh"

#if _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace behh {
namespace system_functions {

int32_t is_port_available(const int32_t& port);

} // namespace system_functions
} // namespace behh

#endif // BEHH_SYSTEM_HH
