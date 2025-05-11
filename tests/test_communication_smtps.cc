#include <becc/functions/communication.hh>
#include <becc/functions/utility.hh>
#include <cassert>
#include <iostream>

struct smtp_conf_t {
    std::string server;
    std::string server_port;
    std::string sender_name;
    std::string sender_address;
    std::string sender_password;
};

int main() {
#if BECC_USING_JSONCPP && BECC_USING_CURL_EXECUTEABLE
    // curl executeable
    {
        // actual config
        // if test_communication_smtps.json doesn't exists
        // copy test_communication_smtps.json.debug and rename to test_communication_smtps.json
        // dont forget to adjust your value test
        const Json::Value CONFIG = becc::utility_functions::jsoncpp::from_json_file("../../../tests/test_communication_smtps.json");

        const std::string TEMPLATE_HTML = "../../../tests/test_communication_smtps.html";
        const std::string TEMPLATE_TITLE = "[ TEST ] - test_communication_smtps";
        const std::string TEMPLATE_RECIPIENT = CONFIG["recipient"].asString();

        smtp_conf_t smtps_conf;
        smtps_conf.server = CONFIG["smtp"]["server"].asString();
        smtps_conf.server_port = CONFIG["smtp"]["server_port"].asString();
        smtps_conf.sender_name = CONFIG["smtp"]["sender_name"].asString();
        smtps_conf.sender_address = CONFIG["smtp"]["sender_address"].asString();
        smtps_conf.sender_password = CONFIG["smtp"]["sender_password"].asString();

        const std::vector<becc::look_and_replace_t> look_and_replaces = {
            {"{TITLE}", TEMPLATE_TITLE},
            {"{RECIPIENT_EMAIL}", TEMPLATE_RECIPIENT}};

        auto result = becc::communication_functions::curl_cmd_impl::smtps_send_mail_by_template_future(
            TEMPLATE_HTML, TEMPLATE_TITLE,
            TEMPLATE_RECIPIENT, look_and_replaces,
            smtps_conf.server, smtps_conf.server_port, smtps_conf.sender_address, smtps_conf.sender_name, smtps_conf.sender_password);

        assert(result.get() == 0);
        std::cout << "passed: test_communication_smtps\n";
    }
#endif // BECC_USING_JSONCPP && BECC_USING_CURL_EXECUTEABLE

    return 1;
}