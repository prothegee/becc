#include <becc/functions/date_and_time.hh>
#include <iostream>
#include <cassert>

int main()
{
    const auto LOCAL_TIME           = becc::date_and_time_functions::local_timezone();

    const auto YYYYMMDD_STR         = becc::date_and_time_functions::utc::YYYYMMDD::to_string_iso8601(LOCAL_TIME);
    const auto YYYYMMDDhhmmss_STR   = becc::date_and_time_functions::utc::YYYYMMDDhhmmss::to_string_human(LOCAL_TIME);
    const auto YYYYMMDDhhmmssms_STR = becc::date_and_time_functions::utc::YYYYMMDDhhmmssms::to_string_human(LOCAL_TIME);
    const auto YYYYMMDDhhmmssµs_STR = becc::date_and_time_functions::utc::YYYYMMDDhhmmssµs::to_string_human(LOCAL_TIME);
    const auto YYYYMMDDhhmmssns_STR = becc::date_and_time_functions::utc::YYYYMMDDhhmmssns::to_string_human(LOCAL_TIME);

    const auto YYYYMMDD_DGT         = becc::date_and_time_functions::utc::YYYYMMDD::to_int(LOCAL_TIME);
    const auto YYYYMMDDhhmmss_DGT   = becc::date_and_time_functions::utc::YYYYMMDDhhmmss::to_int64(LOCAL_TIME);
    const auto YYYYMMDDhhmmssms_DGT = becc::date_and_time_functions::utc::YYYYMMDDhhmmssms::to_int64(LOCAL_TIME);

    const auto YYYYMMDDhhmmss_MLD   = becc::date_and_time_functions::utc::YYYYMMDDhhmmss::to_millis_now(LOCAL_TIME);
    const auto YYYYMMDDhhmmssms_MLD = becc::date_and_time_functions::utc::YYYYMMDDhhmmssms::to_millis_now(LOCAL_TIME);
    const auto YYYYMMDDhhmmssµs_MLD = becc::date_and_time_functions::utc::YYYYMMDDhhmmssµs::to_millis_now(LOCAL_TIME);
    const auto YYYYMMDDhhmmssns_MLD = becc::date_and_time_functions::utc::YYYYMMDDhhmmssns::to_millis_now(LOCAL_TIME);

    const auto YYYYMMDDhhmmss_MLS   = becc::date_and_time_functions::utc::YYYYMMDDhhmmss::to_millis_string(YYYYMMDDhhmmss_MLD);
    const auto YYYYMMDDhhmmssms_MLS = becc::date_and_time_functions::utc::YYYYMMDDhhmmssms::to_millis_string(YYYYMMDDhhmmssms_MLD);
    const auto YYYYMMDDhhmmssµs_MLS = becc::date_and_time_functions::utc::YYYYMMDDhhmmssµs::to_millis_string(YYYYMMDDhhmmssµs_MLD);
    const auto YYYYMMDDhhmmssns_MLS = becc::date_and_time_functions::utc::YYYYMMDDhhmmssns::to_millis_string(YYYYMMDDhhmmssns_MLD);

    std::cout << "[STR] YYYYMMDD         : " << YYYYMMDD_STR << "\n";
    std::cout << "[STR] YYYYMMDDhhmmss   : " << YYYYMMDDhhmmss_STR << "\n";
    std::cout << "[STR] YYYYMMDDhhmmssms : " << YYYYMMDDhhmmssms_STR << "\n";
    std::cout << "[STR] YYYYMMDDhhmmssµs : " << YYYYMMDDhhmmssµs_STR << "\n";
    std::cout << "[STR] YYYYMMDDhhmmssns : " << YYYYMMDDhhmmssns_STR << "\n";
    std::cout << "\n";
    std::cout << "[DGT] YYYYMMDD         : " << YYYYMMDD_DGT << "\n";
    std::cout << "[DGT] YYYYMMDDhhmmss   : " << YYYYMMDDhhmmss_DGT << "\n";
    std::cout << "[DGT] YYYYMMDDhhmmssms : " << YYYYMMDDhhmmssms_DGT << "\n";
    std::cout << "[DGT] YYYYMMDDhhmmssµs : " << "no can do, it's overflow" << "\n";
    std::cout << "[DGT] YYYYMMDDhhmmssns : " << "no can do, it's overflow" << "\n";
    std::cout << "\n";
    std::cout << "[MLD] YYYYMMDDhhmmss   : " << YYYYMMDDhhmmss_MLD << "\n"; 
    std::cout << "[MLD] YYYYMMDDhhmmssms : " << YYYYMMDDhhmmssms_MLD << "\n";
    std::cout << "[MLD] YYYYMMDDhhmmssµs : " << YYYYMMDDhhmmssµs_MLD << "\n";
    std::cout << "[MLD] YYYYMMDDhhmmssns : " << YYYYMMDDhhmmssns_MLD << "\n";
    std::cout << "\n";
    std::cout << "[MLS] YYYYMMDDhhmmss   : " << YYYYMMDDhhmmss_MLS << "\n";
    std::cout << "[MLS] YYYYMMDDhhmmssms : " << YYYYMMDDhhmmssms_MLS << "\n";
    std::cout << "[MLS] YYYYMMDDhhmmssµs : " << YYYYMMDDhhmmssµs_MLS << "\n";
    std::cout << "[MLS] YYYYMMDDhhmmssns : " << YYYYMMDDhhmmssns_MLS << "\n";
    std::cout << "\n";

    return 0;
}