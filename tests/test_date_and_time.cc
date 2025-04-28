#include <becc/functions/date_and_time.hh>
#include <iostream>
#include <cassert>

int main()
{
    std::cout << "YYYYMMDD        : " << becc::date_and_time_functions::utc::YYYYMMDD::to_string_iso8601() << "\n";
    std::cout << "YYYYMMDDhhmmss  : " << becc::date_and_time_functions::utc::YYYYMMDDhhmmss::to_string_human() << "\n";
    std::cout << "YYYYMMDDhhmmssms: " << becc::date_and_time_functions::utc::YYYYMMDDhhmmssms::to_string_human() << "\n";
    std::cout << "YYYYMMDDhhmmssµs: " << becc::date_and_time_functions::utc::YYYYMMDDhhmmssµs::to_string_human() << "\n";
    std::cout << "YYYYMMDDhhmmssns: " << becc::date_and_time_functions::utc::YYYYMMDDhhmmssns::to_string_human() << "\n";

    return 0;
}