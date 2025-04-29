#ifndef BECC_COMMUNICATION_HH
#define BECC_COMMUNICATION_HH
#include "../becc.hh"
#include "../types/look_type.hh"

#if BECC_USING_JSONCPP
#include <json/json.h>
#endif // BECC_USING_JSONCPP

#if BECC_USING_DROGON
#include <drogon/drogon.h>
#endif // BECC_USING_DROGON

#include <future>

namespace becc
{
namespace communication_functions
{

#if BECC_USING_CURL_EXECUTEABLE
namespace curl_cmd_impl
{
/**
 * @brief secure smtp send email by template using curl executeable
 * 
 * @param template_html template html file
 * @param template_title head title
 * @param template_recipient email recipient
 * @param template_look_and_teplace look and replace array
 * @param smtp_server e.g. smtp.domain.tld
 * @param smtp_port e.g. 465
 * @param smtp_sender_address e.g. no-reply@foo.bar
 * @param smtp_sender_name e.g. no-reply
 * @param smtp_sender_password e.g. your_smtp_password_123
 * @return std::future<int32_t> 0 mean ok
 */
std::future<int32_t> smtps_send_mail_by_template_future(const std::string& template_html, const std::string& template_title, const std::string& template_recipient, const std::vector<look_and_replace_t>& template_look_and_teplace, const std::string& smtp_server, const std::string& smtp_port, const std::string& smtp_sender_address, const std::string& smtp_sender_name, const std::string& smtp_sender_password);
} // namespace curl_cmd_impl
#endif // BECC_USING_CURL_EXECUTEABLE

#if BECC_USING_DROGON
namespace drogon_sparkpost_impl
{
/**
 * @brief send mail by template future using drogon to sparkpost
 * 
 * @param template_html template html file
 * @param template_title head title
 * @param template_recipient email recipient
 * @param template_look_and_replace look and replace array
 * @param sparkpost_api_key your_sparkpost_api_key
 * @param sparkpost_sender_name e.g. no-reply@domain.tld
 * @param sparkpost_url e.g. https://api.sparkpost.com
 * @param sparkpost_endpoint e.g. /api/v1/transmissions
 * @param sender_user_agent your sender user agent, default is "org.drogon-sparkpost"
 * @param enable_tracking if true, some url will change to click not as original data pass from templateLookAndReplace
 * @return std::future<int32_t> 0 mean ok
 */
std::future<int32_t> send_mail_by_template_future(const std::string& template_html, const std::string& template_title, const std::string& template_recipient, const std::vector<look_and_replace_t>& template_look_and_replace, const std::string& sparkpost_api_key, const std::string& sparkpost_sender_name, const std::string& sparkpost_url, const std::string& sparkpost_endpoint, const std::string& sender_user_agent = "org.drogon-sparkpost", const bool& enable_tracking = false);
} // namespace drogon_sparkpost_impl
#endif // BECC_USING_DROGON

} // communication_functions
} // namespace becc

#endif // BECC_COMMUNICATION_HH
