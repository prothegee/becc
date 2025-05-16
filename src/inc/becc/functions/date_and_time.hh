#ifndef BEC_DATE_AND_TIMES_HH
#define BEC_DATE_AND_TIMES_HH
#include <becc/becc.hh>

namespace becc {
namespace date_and_time_functions {

/**
 * @brief get this local machine timezone
 *
 * @return int32_t
 */
int32_t local_timezone();

namespace utc {

namespace time_zone {

/**
 * @brief get current time string with time offset option with ISO8601
 *
 * @param time_offset default 0
 * @param ISO8601 default false, if true YYYY-MM-DDThh:mm:ss otherwise YYYY-MM-DD hh:mm:ss
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0, const bool& ISO8601 = false);

} // namespace time_zone

namespace year {

/**
 * @brief get current year as int
 *
 * @param time_offset default 0
 * @return int32_t
 */
int32_t to_int(const int32_t& time_offset = 0);

/**
 * @brief get current year as string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

} // namespace year

namespace month {

/**
 * @brief get current month as int
 *
 * @param time_offset default 0
 * @return int32_t
 */
int32_t to_int(const int32_t& time_offset = 0);

/**
 * @brief get current month as string
 *
 * @param time_offset default 0
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

/**
 * @brief get current month as human string, e.g. Jan, Jun, Jul, etc.
 *
 * @param language 1:en (english) 2:id (bahasa)
 * @param time_offset default 0
 * @return std::string
 */
std::string to_string_human(const int32_t& language = 1, const int32_t& time_offset = 0);

} // namespace month

namespace day {

/**
 * @brief get current day as int
 *
 * @param time_offset default 0
 * @return int32_t
 */
int32_t to_int(const int32_t& time_offset = 0);

/**
 * @brief get current day as string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

} // namespace day

namespace hour {

/**
 * @brief get current hour as int
 *
 * @param time_offset default 0
 * @return int32_t
 */
int32_t to_int(const int32_t& time_offset = 0);

/**
 * @brief get current hour as string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

} // namespace hour

namespace minute {

/**
 * @brief get current minute as int
 *
 * @param time_offset default 0
 * @return int32_t
 */
int32_t to_int(const int32_t& time_offset = 0);

/**
 * @brief get current minute as string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

} // namespace minute

namespace second {

/**
 * @brief get current second as int
 *
 * @param time_offset default 0
 * @return int32_t
 */
int32_t to_int(const int32_t& time_offset = 0);

/**
 * @brief get current second as string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

} // namespace second

namespace YYYYMMDD {

/**
 * @brief get year, month, & day as yyyymmdd int
 *
 * @param time_offset
 * @return int32_t
 */
int32_t to_int(const int32_t& time_offset = 0);

/**
 * @brief get year, month, & day as yyyymmdd string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

/**
 * @brief get year, month, & day as yyyy-mm-dd string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string_iso8601(const int32_t& time_offset = 0);

} // namespace YYYYMMDD

namespace hhmmss {

/**
 * @brief get hour, minute, & second as hhmmss int
 *
 * @param time_offset
 * @return int32_t
 */
int32_t to_int(const int32_t& time_offset = 0);

/**
 * @brief get hour, minute, & second as hhmmss string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

/**
 * @brief get hour, minute, & second as hh:mm:ss sting
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string_human(const int32_t& time_offset = 0);

} // namespace hhmmss

namespace YYYYMMDDhhmmss {

/**
 * @brief get YYYYMMDDhhmmss as int64
 *
 * @param time_offset
 * @return int64_t
 */
int64_t to_int64(const int32_t& time_offset = 0);

/**
 * @brief convert YYYYMMDDhhmmss to millis
 *
 * @param YYYYMMDDhhmmss
 * @return int64_t
 */
int64_t to_millis(const std::string& YYYYMMDDhhmmss);

/**
 * @brief use current date and time as millis
 *
 * @param time_offset
 * @return int64_t
 */
int64_t to_millis_now(const int32_t& time_offset = 0);

/**
 * @brief YYYYMMDDhhmmss to milis timestring, as YYYY-MM-DDThh:mm:ss or YYYY-MM-DD hh:mm:ss if use_time_sign = false
 *
 * @param YYYYMMDDhhmmssms
 * @param use_time_sign
 * @return std::string
 */
std::string to_millis_string(const int64_t& YYYYMMDDhhmmssms, const bool& use_time_sign = false);

/**
 * @brief get YYYYMMDDhhmmss as is
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

/**
 * @brief get YYYYMMDDhhmmss as YYYY-MM-DDThh:mm:ss or YYYY-MM-DD hh:mm:ss if use_time_sign = false
 *
 * @param time_offset
 * @param use_time_sign
 * @return std::string
 */
std::string to_string_human(const int32_t& time_offset = 0, const bool& use_time_sign = false);

/**
 * @brief get YYYYMMDDhhmmss without time offset limit
 *
 * @param seconds_offset
 * @return std::string
 */
std::string to_string_seconds_offset(const int32_t& seconds_offset = 0);

} // namespace YYYYMMDDhhmmss

namespace YYYYMMDDhhmmssms {

/**
 * @brief get YYYYMMDDhhmmssms as int64
 *
 * @param time_offset
 * @return int64_t
 */
int64_t to_int64(const int32_t& time_offset = 0);

/**
 * @brief convert YYYYMMDDhhmmssms to millis
 *
 * @param YYYYMMDDhhmmssms
 * @return int64_t
 */
int64_t to_millis(const std::string& YYYYMMDDhhmmssms);

/**
 * @brief get YYYYMMDDhhmmssms as millis
 *
 * @param time_offset
 * @return int64_t
 */
int64_t to_millis_now(const int32_t& time_offset = 0);

/**
 * @brief YYYYMMDDhhmmssms to milis timestring, as YYYY-MM-DDThh:mm:ss.xxx or YYYY-MM-DD hh:mm:ss.xxx if use_time_sign = false
 *
 * @param YYYYMMDDhhmmssms
 * @param use_time_sign
 * @return std::string
 */
std::string to_millis_string(const int64_t& YYYYMMDDhhmmssms, const bool& use_time_sign = false);

/**
 * @brief get YYYYMMDDhhmmssms as is string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

/**
 * @brief get YYYYMMDDhhmmssms as YYYY-MM-DDThh:mm:ss.sss or YYYY-MM-DD hh:mm:ss.sss if use_time_sign = false
 *
 * @param time_offset
 * @param use_time_sign
 * @return std::string
 */
std::string to_string_human(const int32_t& time_offset = 0, const bool& use_time_sign = false);

/**
 * @brief get YYYYMMDDhhmmssms without time offset limit
 *
 * @param seconds_offset
 * @return std::string
 */
std::string to_string_second_offset(const int32_t& seconds_offset = 0);

} // namespace YYYYMMDDhhmmssms

namespace YYYYMMDDhhmmssus {

/**
 * @brief convert YYYYMMDDhhmmssus to millis
 *
 * @param YYYYMMDDhhmmssus
 * @return int64_t
 */
int64_t to_millis(const std::string& YYYYMMDDhhmmssus);

/**
 * @brief get YYYYMMDDhhmmssus as millis
 *
 * @param time_offset
 * @return int64_t
 */
int64_t to_millis_now(const int32_t& time_offset = 0);

/**
 * @brief YYYYMMDDhhmmssus to milis timestring, as YYYY-MM-DDThh:mm:ss.xxxxxx or YYYY-MM-DD hh:mm:ss.xxxxx if use_time_sign = false
 *
 * @param YYYYMMDDhhmmssus
 * @param use_time_sign
 * @return std::string
 */
std::string to_millis_string(const int64_t& YYYYMMDDhhmmssus, const bool& use_time_sign = false);

/**
 * @brief get YYYYMMDDhhmmssus as is string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

/**
 * @brief get YYYYMMDDhhmmssus as YYYY-MM-DDThh:mm:ss.ssssss or YYYY-MM-DD hh:mm:ss.ssssss if use_time_sign = false
 *
 * @param time_offset
 * @param use_time_sign
 * @return std::string
 */
std::string to_string_human(const int32_t& time_offset = 0, const bool& use_time_sign = false);

/**
 * @brief get YYYYMMDDhhmmssus without time offset limit
 *
 * @param seconds_offset
 * @return std::string
 */
std::string to_string_second_offset(const int32_t& seconds_offset = 0);

} // namespace YYYYMMDDhhmmssus

namespace YYYYMMDDhhmmssns {

/**
 * @brief convert YYYYMMDDhhmmssns to millis
 *
 * @param YYYYMMDDhhmmssns
 * @return int64_t
 */
int64_t to_millis(const std::string& YYYYMMDDhhmmssns);

/**
 * @brief get YYYYMMDDhhmmssns as millis
 *
 * @param time_offset
 * @return int64_t
 */
int64_t to_millis_now(const int32_t& time_offset = 0);

/**
 * @brief YYYYMMDDhhmmssns to milis timestring, as YYYY-MM-DDThh:mm:ss.xxxxxxxxx or YYYY-MM-DD hh:mm:ss.xxxxxxxxx if use_time_sign = false
 *
 * @param YYYYMMDDhhmmssns
 * @param use_time_sign
 * @return std::string
 */
std::string to_millis_string(const int64_t& YYYYMMDDhhmmssns, const bool& use_time_sign = false);

/**
 * @brief get YYYYMMDDhhmmssns as is string
 *
 * @param time_offset
 * @return std::string
 */
std::string to_string(const int32_t& time_offset = 0);

/**
 * @brief get YYYYMMDDhhmmssns as YYYY-MM-DDThh:mm:ss.sssssssss or YYYY-MM-DD hh:mm:ss.sssssssss if use_time_sign = false
 *
 * @param time_offset
 * @param use_time_sign
 * @return std::string
 */
std::string to_string_human(const int32_t& time_offset = 0, const bool& use_time_sign = false);

/**
 * @brief get YYYYMMDDhhmmssns without time offset limit
 *
 * @param seconds_offset
 * @return std::string
 */
std::string to_string_second_offset(const int32_t& seconds_offset = 0);

} // namespace YYYYMMDDhhmmssns

} // namespace utc

} // namespace date_and_time_functions
} // namespace becc

#endif // BEC_DATE_AND_TIMES_HH
