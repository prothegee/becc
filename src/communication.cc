#include <becc/functions/communication.hh>
#include <becc/functions/utility.hh>

#include <fstream>
#include <iostream>

namespace becc
{
namespace communication_functions
{

#if BECC_USING_CURL_EXECUTEABLE
namespace curl_cmd_impl
{
std::future<int32_t> smtps_send_mail_by_template_future(const std::string& template_html, const std::string& template_title, const std::string& template_recipient, const std::vector<look_and_replace_t>& template_look_and_teplace, const std::string& smtp_server, const std::string& smtp_port, const std::string& smtp_sender_address, const std::string& smtp_sender_name, const std::string& smtp_sender_password)
{
    std::promise<int32_t> response_promise;
    std::future<int32_t> response_future = response_promise.get_future();

    std::ifstream file(template_html);
    std::stringstream html;

    std::string RECIPIENT_ADDRESS, RECIPIENT_SUBJECT, RECIPIENT_CONTENT, RECIPIENT_CONTENT_HTML, RECIPIENT_PASSCODE, CMD;

        CMD = R"(curl --ssl-reqd --url "smtps://{SMTP_SERVER}:{SMTP_PORT}" \
--silent \
--user "{SMTP_USER}:{SMTP_PASSWD}" \
--mail-from "{SMTP_USER}" \
--mail-rcpt "{RECIPIENT_ADDRESS}" \
--upload-file - << EOF
From: {SMTP_SENDER} <{SMTP_USER}>
To: {RECIPIENT_ADDRESS}
Subject: {RECIPIENT_SUBJECT}
Content-Type: text/html; charset="UTF-8"

{RECIPIENT_CONTENT}
)";

    if (!file)
    {
        std::cerr << "curl_cmd_impl::send_mail_by_template_future: can't find template html\n";
        response_promise.set_value(-1);
        return response_future;
    }

    html << file.rdbuf();
    RECIPIENT_CONTENT_HTML = html.str();

    for (auto &data : template_look_and_teplace)
    {
        utility_functions::find::and_replace_all(RECIPIENT_CONTENT_HTML, data.to_look, data.to_replace);
    }

    RECIPIENT_ADDRESS = template_recipient;
    RECIPIENT_SUBJECT = template_title;
    RECIPIENT_CONTENT = RECIPIENT_CONTENT_HTML;

    utility_functions::find::and_replace_all(CMD, "{SMTP_SERVER}", smtp_server);
    utility_functions::find::and_replace_all(CMD, "{SMTP_PORT}", smtp_port);
    utility_functions::find::and_replace_all(CMD, "{SMTP_USER}", smtp_sender_address);
    utility_functions::find::and_replace_all(CMD, "{SMTP_PASSWD}", smtp_sender_password);
    utility_functions::find::and_replace_all(CMD, "{SMTP_SENDER}", smtp_sender_name);
    utility_functions::find::and_replace_all(CMD, "{RECIPIENT_ADDRESS}", RECIPIENT_ADDRESS);
    utility_functions::find::and_replace_all(CMD, "{RECIPIENT_SUBJECT}", RECIPIENT_SUBJECT);
    utility_functions::find::and_replace_all(CMD, "{RECIPIENT_CONTENT}", RECIPIENT_CONTENT);

    if (std::thread::hardware_concurrency() >= 2)
    {
        #if BECC_IS_DEBUG
        std::cout << "DEBUG: curl_cmd_impl::send_mail_by_template_future: system has multiple threads\n";
        #endif // BECC_IS_DEBUG

        auto status = std::async(std::launch::async, system, CMD.c_str());

        if (status.get() == 0)
        {
            response_promise.set_value(1);
        }
        else
        {
            response_promise.set_value(-2);
        }
    }
    else
    {
        #if BECC_IS_DEBUG
        std::cout << "DEBUG: curl_cmd_impl::send_mail_by_template_future: system has single thread\n";
        #endif // BECC_IS_DEBUG

        auto status = system(CMD.c_str());

        if (status == 0)
        {
            response_promise.set_value(1);
        }
        else
        {
            response_promise.set_value(-3);
        }
    }
    file.close();

    return response_future;
}
} // namespace curl_cmd_impl
#endif // BECC_USING_CURL_EXECUTEABLE

#if BECC_USING_DROGON
namespace drogon_sparkpost_impl
{
std::future<int32_t> send_mail_by_template_future(const std::string& template_html, const std::string& template_title, const std::string& template_recipient, const std::vector<look_and_replace_t>& template_look_and_replace, const std::string& sparkpost_api_key, const std::string& sparkpost_sender_name, const std::string& sparkpost_url, const std::string& sparkpost_endpoint, const std::string& sender_user_agent, const bool& enable_tracking)
{
    std::promise<int32_t> response_promise;
    std::future<int32_t> response_future = response_promise.get_future();

    std::ifstream file(template_html);
    std::stringstream html;

    if (!file)
        {
            std::cerr << "drogon_sparkpost_impl::send_mail_by_template_future: can't find the template html\n";
            response_promise.set_value(-1);
            return response_future;
        }

        std::string RECIPIENT_CONTENT_HTML;

        Json::Value root, content, recipients, options;

        html << file.rdbuf();
        RECIPIENT_CONTENT_HTML = html.str();

        for (auto &data : template_look_and_replace)
        {
            utility_functions::find::and_replace_all(RECIPIENT_CONTENT_HTML, data.to_look, data.to_replace);
        }

        content["from"] = sparkpost_sender_name;
        content["subject"] = template_title;
        content["text"] = RECIPIENT_CONTENT_HTML;
        content["html"] = RECIPIENT_CONTENT_HTML;

        recipients["address"] = template_recipient;

        root["content"] = content;
        root["recipients"].append(recipients);
        root["options"]["click_tracking"] = enable_tracking;

        auto pClient = drogon::HttpClient::newHttpClient(sparkpost_url);
        auto pRequest = drogon::HttpRequest::newHttpJsonRequest(root);

        pClient->setUserAgent(sender_user_agent);

        pRequest->setPath(sparkpost_endpoint);
        pRequest->setContentTypeCode(drogon::CT_APPLICATION_JSON);
        pRequest->addHeader("accept", "*/*");
        pRequest->addHeader("authorization", sparkpost_api_key);
        pRequest->setMethod(drogon::Post);

        pClient->sendRequest(pRequest, [&response_promise](drogon::ReqResult result, const drogon::HttpResponsePtr &pResp)
        {
            if (result == drogon::ReqResult::Ok && pResp->getStatusCode() == drogon::k200OK)
            {
                #if BECC_IS_DEBUG
                std::cout << "drogon_sparkpost_impl::send_mail_by_template_future: reponse ok\n";
                #endif // LIBPRCPP_IS_DEBUG

                response_promise.set_value(1);
            }
            else
            {
                #if BECC_IS_DEBUG
                std::cout << "drogon_sparkpost_impl::send_mail_by_template_future: status code is " << pResp->getStatusCode() << "\n";
                #endif // LIBPRCPP_IS_DEBUG
                response_promise.set_value(-2);
            }
        });

        file.close();

    return response_future;
}
} // namespace drogon_sparkpost_impl
#endif // BECC_USING_DROGON

} // communication_functions
} // namespace becc
