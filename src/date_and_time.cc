#include <behh/functions/date_and_time.hh>

#include <chrono>
#include <iomanip>
#include <sstream>

namespace behh {
namespace date_and_time_functions {

int32_t local_timezone() {
    std::time_t now = std::time(nullptr);
    std::tm utc_time{};
    std::tm local_time{};

#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now, &utc_time);
    localtime_r(&now, &local_time);
#else
    gmtime_s(&utc_time, &now);
    localtime_s(&local_time, &now);
#endif

    std::time_t utc_time_t = std::mktime(&utc_time);
    std::time_t local_time_t = std::mktime(&local_time);

    int32_t offset = static_cast<int32_t>(local_time_t - utc_time_t);
    return offset / 3600;
}

namespace utc {

namespace time_zone {

std::string to_string(const int32_t& time_offset, const bool& ISO8601) {
    std::string result;
    std::string negative_or_positive, utc_format;
    std::stringstream ss;

    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    if (timezone_offset <= -1) {
        negative_or_positive = "";
    }
    if (timezone_offset >= 0) {
        negative_or_positive = "+";
    }

    if (timezone_offset >= 0 && timezone_offset <= 9) {
        utc_format = "0" + std::to_string(timezone_offset);
    } else if (timezone_offset <= -1 && timezone_offset >= -9) {
        utc_format = std::to_string(timezone_offset);
        utc_format.insert(1, "0");
    } else {
        utc_format = std::to_string(timezone_offset);
    }

    utc_format += ":00";

    auto adjustTimeOffset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjustTimeOffset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    if (ISO8601) {
        ss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S");
    } else {
        ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
    }

    result = ss.str();

    if (ISO8601) {
        result += negative_or_positive;
        result += utc_format;
    } else {
        result += " ";
        result += negative_or_positive;
        result += utc_format;
    }

    return result;
}

} // namespace time_zone

namespace year {

int32_t to_int(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%Y");

    result = ss.str();

    return std::stoi(result);
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%Y");

    result = ss.str();

    return result;
}

} // namespace year

namespace month {

int32_t to_int(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%m");

    result = ss.str();

    if (result.rfind("0", 0) == 0) {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%m");

    result = ss.str();

    if (result.at(0) == '0') {
        result.replace(0, 1, "");
    }

    return result;
}

std::string to_string_human(const int32_t& language, const int32_t& time_offset) {
    std::string result, tmp_str1;

    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%m");

    tmp_str1 = ss.str();

    if (tmp_str1.rfind("0", 0) == 0) {
        tmp_str1.replace(0, 1, "");
    }

    const auto month = std::stoi(tmp_str1);

    result = "";

    switch (language) {
    case 1: {
        if (month == 1) {
            result = "Jan";
        }
        if (month == 2) {
            result = "Feb";
        }
        if (month == 3) {
            result = "Mar";
        }
        if (month == 4) {
            result = "Apr";
        }
        if (month == 5) {
            result = "May";
        }
        if (month == 6) {
            result = "Jun";
        }
        if (month == 7) {
            result = "Jul";
        }
        if (month == 8) {
            result = "Aug";
        }
        if (month == 9) {
            result = "Sep";
        }
        if (month == 10) {
            result = "Oct";
        }
        if (month == 11) {
            result = "Nov";
        }
        if (month == 12) {
            result = "Dec";
        }
    } break;

    case 2: {
        if (month == 1) {
            result = "Jan";
        }
        if (month == 2) {
            result = "Feb";
        }
        if (month == 3) {
            result = "Mar";
        }
        if (month == 4) {
            result = "Apr";
        }
        if (month == 5) {
            result = "Mei";
        }
        if (month == 6) {
            result = "Jun";
        }
        if (month == 7) {
            result = "Jul";
        }
        if (month == 8) {
            result = "Agu";
        }
        if (month == 9) {
            result = "Sep";
        }
        if (month == 10) {
            result = "Okt";
        }
        if (month == 11) {
            result = "Nov";
        }
        if (month == 12) {
            result = "Des";
        }
    } break;

    default: {
        if (month == 1) {
            result = "Jan";
        }
        if (month == 2) {
            result = "Feb";
        }
        if (month == 3) {
            result = "Mar";
        }
        if (month == 4) {
            result = "Apr";
        }
        if (month == 5) {
            result = "May";
        }
        if (month == 6) {
            result = "Jun";
        }
        if (month == 7) {
            result = "Jul";
        }
        if (month == 8) {
            result = "Aug";
        }
        if (month == 9) {
            result = "Sep";
        }
        if (month == 10) {
            result = "Oct";
        }
        if (month == 11) {
            result = "Nov";
        }
        if (month == 12) {
            result = "Dec";
        }
    } break;
    }

    return result;
}

} // namespace month

namespace day {

int32_t to_int(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%d");

    result = ss.str();

    if (result.at(0) == '0') {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%d");

    result = ss.str();

    if (result.at(0) == '0') {
        result.replace(0, 1, "");
    }

    return result;
}

} // namespace day

namespace hour {

int32_t to_int(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%H");

    result = ss.str();

    if (result.at(0) == '0') {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%H");

    result = ss.str();

    if (result.at(0) == '0') {
        result.replace(0, 1, "");
    }

    return result;
}

} // namespace hour

namespace minute {

int32_t to_int(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%M");

    result = ss.str();

    if (result.at(0) == '0') {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%M");

    result = ss.str();

    if (result.at(0) == '0') {
        result.replace(0, 1, "");
    }

    return result;
}

} // namespace minute

namespace second {

int32_t to_int(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%S");

    result = ss.str();

    if (result.at(0) == '0') {
        result.replace(0, 1, "");
    }

    return std::stoi(result);
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%S");

    result = ss.str();

    if (result.at(0) == '0') {
        result.replace(0, 1, "");
    }

    return result;
}

} // namespace second

namespace YYYYMMDD {

int32_t to_int(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%Y%m%d");

    result = ss.str();

    return std::stoi(result);
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%Y%m%d");

    result = ss.str();

    return result;
}

std::string to_string_iso8601(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%Y-%m-%d");

    result = ss.str();

    return result;
}

} // namespace YYYYMMDD

namespace hhmmss {

int32_t to_int(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%H%M%S");

    result = ss.str();

    return std::stol(result);
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%H%M%S");

    result = ss.str();

    return result;
}

std::string to_string_human(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%H:%M:%S");

    result = ss.str();

    return result;
}

} // namespace hhmmss

namespace YYYYMMDDhhmmss {

int64_t to_int64(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S");

    result = ss.str();

    return std::stoll(result);
}

int64_t to_millis(const std::string& YYYYMMDDhhmmss) {
    int64_t result;

    std::tm time = {};
    std::istringstream ss(YYYYMMDDhhmmss);

    if (YYYYMMDDhhmmss.find("T") != std::string::npos) {
        ss >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");
    } else {
        ss >> std::get_time(&time, "%Y-%m-%d %H:%M:%S");
    }

    if (ss.fail()) {
        throw std::runtime_error("ERROR YYYYMMDDhhmmss: Failed to parse time string");
    }

    time_t time_since_epoch = mktime(&time);

    result = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::from_time_t(time_since_epoch).time_since_epoch()).count();

    return result;
}

int64_t to_millis_now(const int32_t& time_offset) {
    const int32_t tz_offset = std::max(-12, std::min(time_offset, 14));

    auto now = std::chrono::system_clock::now();
    auto adjusted = now + std::chrono::hours(tz_offset);

    return std::chrono::duration_cast<std::chrono::milliseconds>(
               adjusted.time_since_epoch())
        .count();
}

std::string to_millis_string(const int64_t& YYYYMMDDhhmmss, const bool& use_time_sign) {
    std::chrono::system_clock::time_point tp{std::chrono::milliseconds{YYYYMMDDhhmmss}};
    time_t tt = std::chrono::system_clock::to_time_t(tp);
    std::tm* tm = std::gmtime(&tt);
    std::stringstream ss;
    ss << (use_time_sign ? std::put_time(tm, "%Y-%m-%dT%H:%M:%S") : std::put_time(tm, "%Y-%m-%d %H:%M:%S"));
    return ss.str();
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S");

    result = ss.str();

    return result;
}

std::string to_string_human(const int32_t& time_offset, const bool& use_time_sign) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    if (use_time_sign) {
        ss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S");
    } else {
        ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
    }

    result = ss.str();

    return result;
}

std::string to_string_seconds_offset(const int32_t& seconds_offset) {
    std::string result;
    std::stringstream ss;

    auto now = std::chrono::system_clock::now();

    auto seconds = std::chrono::seconds(seconds_offset);

    auto future_time = now + seconds;

    std::time_t future_time_t = std::chrono::system_clock::to_time_t(future_time);

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&future_time_t, &tm_buf);
#else
    gmtime_s(&tm_buf, &future_time_t);
#endif

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S");

    result = ss.str();

    return result;
}

} // namespace YYYYMMDDhhmmss

namespace YYYYMMDDhhmmssms {

int64_t to_int64(const int32_t& time_offset) {
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto milliseconds = now_ms.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S") << std::setw(3) << std::setfill('0') << milliseconds.count();

    return std::stoll(ss.str());
}

int64_t to_millis(const std::string& YYYYMMDDhhmmssms) {
    int64_t result;

    std::tm time = {};
    std::istringstream ss(YYYYMMDDhhmmssms);

    if (YYYYMMDDhhmmssms.find("T") != std::string::npos) {
        ss >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");
    } else {
        ss >> std::get_time(&time, "%Y-%m-%d %H:%M:%S");
    }

    if (ss.fail()) {
        throw std::runtime_error("ERROR YYYYMMDDhhmmssms: Failed to parse time string");
    }

    time_t time_since_epoch = mktime(&time);

    result = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::from_time_t(time_since_epoch).time_since_epoch()).count();

    return result;
}

int64_t to_millis_now(const int32_t& time_offset) {
    int32_t timezone_offset = std::max(-12, std::min(time_offset, 14));
    auto now = std::chrono::system_clock::now();

    auto adjusted = now + std::chrono::seconds(timezone_offset * 3600);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(adjusted.time_since_epoch());
    return duration.count();
}

std::string to_millis_string(const int64_t& YYYYMMDDhhmmssms, const bool& use_time_sign) {
    std::chrono::system_clock::time_point tp{std::chrono::milliseconds{YYYYMMDDhhmmssms}};
    time_t tt = std::chrono::system_clock::to_time_t(tp);
    std::tm* tm = std::gmtime(&tt);
    std::stringstream ss;
    ss << (use_time_sign ? std::put_time(tm, "%Y-%m-%dT%H:%M:%S") : std::put_time(tm, "%Y-%m-%d %H:%M:%S"));
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()) % 1000;
    ss << "." << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto milliseconds = now_ms.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S") << std::setw(3) << std::setfill('0') << milliseconds.count();

    result = ss.str();

    return result;
}

std::string to_string_human(const int32_t& time_offset, const bool& use_time_sign) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto milliseconds = now_ms.time_since_epoch() % std::chrono::seconds(1);

    if (use_time_sign) {
        ss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();
    } else {
        ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();
    }

    result = ss.str();

    return result;
}

std::string to_string_second_offset(const int32_t& seconds_offset) {
    std::string result;
    std::stringstream ss;

    auto now = std::chrono::system_clock::now();

    auto seconds = std::chrono::seconds(seconds_offset);

    auto future_time = now + seconds;

    std::time_t future_time_t = std::chrono::system_clock::to_time_t(future_time);

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&future_time_t, &tm_buf);
#else
    gmtime_s(&tm_buf, &future_time_t);
#endif

    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto milliseconds = now_ms.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S") << std::setw(3) << std::setfill('0') << milliseconds.count();

    result = ss.str();

    return result;
}

} // namespace YYYYMMDDhhmmssms

namespace YYYYMMDDhhmmssus {

int64_t to_millis(const std::string& YYYYMMDDhhmmssus) {
    int64_t result;

    std::tm time = {};
    std::istringstream ss(YYYYMMDDhhmmssus);

    if (YYYYMMDDhhmmssus.find("T") != std::string::npos) {
        ss >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");
    } else {
        ss >> std::get_time(&time, "%Y-%m-%d %H:%M:%S");
    }

    if (ss.fail()) {
        throw std::runtime_error("ERROR YYYYMMDDhhmmssus: Failed to parse time string");
    }

    time_t time_since_epoch = mktime(&time);

    result = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::from_time_t(time_since_epoch).time_since_epoch()).count();

    return result;
}

int64_t to_millis_now(const int32_t& time_offset) {
    int32_t timezone_offset = std::max(-12, std::min(time_offset, 14));
    auto now = std::chrono::system_clock::now();

    auto adjusted = now + std::chrono::seconds(timezone_offset * 3600);

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(adjusted.time_since_epoch());
    return duration.count();
}

std::string to_millis_string(const int64_t& YYYYMMDDhhmmssus, const bool& use_time_sign) {
    std::chrono::system_clock::time_point tp{std::chrono::microseconds{YYYYMMDDhhmmssus}};
    time_t tt = std::chrono::system_clock::to_time_t(tp);
    std::tm* tm = std::gmtime(&tt);
    std::stringstream ss;
    ss << (use_time_sign ? std::put_time(tm, "%Y-%m-%dT%H:%M:%S") : std::put_time(tm, "%Y-%m-%d %H:%M:%S"));
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch()) % 1000000;
    ss << "." << std::setfill('0') << std::setw(6) << us.count();
    return ss.str();
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    auto now_mcs = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto microseconds = now_mcs.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S") << std::setw(6) << std::setfill('0') << microseconds.count();

    result = ss.str();

    return result;
}

std::string to_string_human(const int32_t& time_offset, const bool& use_time_sign) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    auto now_mcs = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto microseconds = now_mcs.time_since_epoch() % std::chrono::seconds(1);

    if (use_time_sign) {
        ss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S") << '.' << std::setw(6) << std::setfill('0') << microseconds.count();
    } else {
        ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(6) << std::setfill('0') << microseconds.count();
    }

    result = ss.str();

    return result;
}

std::string to_string_second_offset(const int32_t& seconds_offset) {
    std::string result;
    std::stringstream ss;

    auto now = std::chrono::system_clock::now();

    auto seconds = std::chrono::seconds(seconds_offset);

    auto future_time = now + seconds;

    std::time_t future_time_t = std::chrono::system_clock::to_time_t(future_time);

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&future_time_t, &tm_buf);
#else
    gmtime_s(&tm_buf, &future_time_t);
#endif

    auto now_mcs = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto microseconds = now_mcs.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S") << std::setw(6) << std::setfill('0') << microseconds.count();

    result = ss.str();

    return result;
}

} // namespace YYYYMMDDhhmmssus

namespace YYYYMMDDhhmmssns {

int64_t to_millis(const std::string& YYYYMMDDhhmmssns) {
    int64_t result;

    std::tm time = {};
    std::istringstream ss(YYYYMMDDhhmmssns);

    if (YYYYMMDDhhmmssns.find("T") != std::string::npos) {
        ss >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");
    } else {
        ss >> std::get_time(&time, "%Y-%m-%d %H:%M:%S");
    }

    if (ss.fail()) {
        throw std::runtime_error("ERROR YYYYMMDDhhmmssns: Failed to parse time string");
    }

    time_t time_since_epoch = mktime(&time);

    result = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::from_time_t(time_since_epoch).time_since_epoch()).count();

    return result;
}

int64_t to_millis_now(const int32_t& time_offset) {
    int32_t timezone_offset = std::max(-12, std::min(time_offset, 14));
    auto now = std::chrono::system_clock::now();

    auto adjusted = now + std::chrono::seconds(timezone_offset * 3600);

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(adjusted.time_since_epoch());
    return duration.count();
}

std::string to_millis_string(const int64_t& YYYYMMDDhhmmssns, const bool& use_time_sign) {
    std::chrono::system_clock::time_point tp;
#if defined(__GNUC__) || defined(__clang__)
    tp = std::chrono::system_clock::time_point{std::chrono::nanoseconds{YYYYMMDDhhmmssns}};
#else
    tp = std::chrono::system_clock::time_point{
        std::chrono::duration_cast<std::chrono::system_clock::duration>(
            std::chrono::nanoseconds{YYYYMMDDhhmmssns})};
#endif

    time_t tt = std::chrono::system_clock::to_time_t(tp);
    std::tm* tm = std::gmtime(&tt);
    std::stringstream ss;
    ss << (use_time_sign ? std::put_time(tm, "%Y-%m-%dT%H:%M:%S") : std::put_time(tm, "%Y-%m-%d %H:%M:%S"));
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()) % 1000000000;
    ss << "." << std::setfill('0') << std::setw(9) << ns.count();
    return ss.str();
}

std::string to_string(const int32_t& time_offset) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto nanoseconds = now_ns.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S") << std::setw(9) << std::setfill('0') << nanoseconds.count();

    result = ss.str();

    return result;
}

std::string to_string_human(const int32_t& time_offset, const bool& use_time_sign) {
    std::string result;
    std::stringstream ss;
    int32_t timezone_offset = time_offset;

    if (timezone_offset <= -12) {
        timezone_offset = -12;
    }
    if (timezone_offset >= 14) {
        timezone_offset = 14;
    }

    auto adjust_time_offset = timezone_offset * 3600;
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::time_t now_time_utc = now_time + adjust_time_offset;

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&now_time_utc, &tm_buf);
#else
    gmtime_s(&tm_buf, &now_time_utc);
#endif

    auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto nanoseconds = now_ns.time_since_epoch() % std::chrono::seconds(1);

    if (use_time_sign) {
        ss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S") << '.' << std::setw(9) << std::setfill('0') << nanoseconds.count();
    } else {
        ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(9) << std::setfill('0') << nanoseconds.count();
    }

    result = ss.str();

    return result;
}

std::string to_string_second_offset(const int32_t& seconds_offset) {
    std::string result;
    std::stringstream ss;

    auto now = std::chrono::system_clock::now();

    auto seconds = std::chrono::seconds(seconds_offset);

    auto future_time = now + seconds;

    std::time_t future_time_t = std::chrono::system_clock::to_time_t(future_time);

    std::tm tm_buf{};
#if defined(__GNUC__) || defined(__clang__)
    gmtime_r(&future_time_t, &tm_buf);
#else
    gmtime_s(&tm_buf, &future_time_t);
#endif

    auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto nanoseconds = now_ns.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(&tm_buf, "%Y%m%d%H%M%S") << std::setw(9) << std::setfill('0') << nanoseconds.count();

    result = ss.str();

    return result;
}

} // namespace YYYYMMDDhhmmssns

} // namespace utc

} // namespace date_and_time_functions
} // namespace behh