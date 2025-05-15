#include <becc/becc.hh>

#if BECC_USING_COUCHBASE_CXX_CLIENT
#include <becc/functions/date_and_time.hh>
#include <becc/functions/utility.hh>
#include <becc/interfaces/icouchbase_core_interface.hh>

#include <spdlog/fmt/bundled/core.h>

#include <mutex>
#include <thread>
#include <future>
#include <chrono>
#include <iostream>
#include <atomic>
#include <system_error>

// main config file for this test
// if doesn't exists, copy the "test_database_couchbase_rw.json.debug" and rename to "test_database_couchbase_rw.json"
INLNSTTCCNST std::string CONFIG_FILE = "../../../tests/test_database_couchbase_rw.json";

std::mutex print_mutex;
class BasicDbTable : public becc::ICouchbaseCoreInterface {
private:
    // tba

public:
    BasicDbTable() {
        const auto CONFIG = becc::utility_functions::jsoncpp::from_json_file(CONFIG_FILE);

        becc::couchbase_connection_t conn;

        conn.host = CONFIG["host"].asString();
        conn.username = CONFIG["username"].asString();
        conn.password = CONFIG["password"].asString();
        conn.scope_name = CONFIG["scope_name"].asString();
        conn.bucket_name = CONFIG["bucket_name"].asString();
        conn.collection_name = CONFIG["collection_name"].asString();

        ICouchbase.initialize_constructor(conn, 6);
    }
    ~BasicDbTable() {
        // 
    }

    /////////////////////////////////////////////////////////////////

    // this is couchbase related table document, similar to cols in postgresql & scylladb columns key
    struct doc_key {
        struct pk {
            INLNSTTCCNST std::string id = "id";
        };
        INLNSTTCCNST std::string random_text = "random_text";
        INLNSTTCCNST std::string random_integer = "random_integer";
        INLNSTTCCNST std::string random_big_integer = "random_big_integer";
        INLNSTTCCNST std::string random_float = "random_float";
        INLNSTTCCNST std::string random_double = "random_double";
        INLNSTTCCNST std::string created_timestamp = "created_timestamp";
        INLNSTTCCNST std::string created_timestring = "created_timestring";
    };

    struct table_data {
        std::string id;
        std::string random_text;
        int32_t     random_integer;
        int64_t     random_big_integer;
        float32_t   random_float;
        float64_t   random_double;
        int64_t     created_timestamp;
        std::string created_timestring;
    }; // struct table_data

    /////////////////////////////////////////////////////////////////

    void initialize_table_index() {
        /* not implemented */
    }

    /////////////////////////////////////////////////////////////////

    void generate_random_data(std::atomic<uint64_t>& count_error_ref, std::atomic<uint64_t>& count_iter_ref, std::atomic<uint64_t>& count_collide_ref, const uint64_t& max_iter) {
        auto& count_error = reinterpret_cast<std::atomic<uint64_t>&>(count_error_ref);
        auto& count_iter = reinterpret_cast<std::atomic<uint64_t>&>(count_iter_ref);
        auto& count_collide = reinterpret_cast<std::atomic<uint64_t>&>(count_collide_ref);

        std::lock_guard<std::mutex> lock1(print_mutex);

        table_data data;
        data.id = becc::utility_functions::generate::uuid::v4();
        data.random_text = becc::utility_functions::generate::random_alphanumeric_with_special_character(32);
        data.random_integer = becc::utility_functions::generate::random_number(10000000, 99999999);
        data.random_big_integer = becc::utility_functions::generate::random_number(10000000000000, 99999999999999);
        data.random_float = becc::utility_functions::generate::random_number(100.00000f, 999.99999f);
        data.random_double = becc::utility_functions::generate::random_number(100000.00000000, 999999.99999999);
        data.created_timestamp = becc::date_and_time_functions::utc::YYYYMMDDhhmmss::to_millis_now();
        data.created_timestring = becc::date_and_time_functions::utc::YYYYMMDDhhmmss::to_millis_string(data.created_timestamp);

        auto collection = ICouchbase.get_collection();

        auto [err, resp] = collection.upsert(
            // primary key
            doc_key::pk::id,
            tao::json::value{
                {doc_key::random_text, data.random_text},
                {doc_key::random_integer, data.random_integer},
                {doc_key::random_big_integer, data.random_big_integer},
                {doc_key::random_float, data.random_float},
                {doc_key::random_double, data.random_double},
                {doc_key::created_timestamp, data.created_timestamp},
                {doc_key::created_timestring, data.created_timestring},
            },
            { /* n/a */ }
        ).get();

        uint64_t current_iter = count_iter.fetch_add(1, std::memory_order_relaxed) + 1;

        // uint64_t error_iter = 0;
        if (err.ec()) {
            count_error += 1;
            // error_iter = count_error.fetch_add(1, std::memory_order_relaxed) + 1;
        }

        if (count_iter <= max_iter) {
            std::cout << "\r         \r";
            std::cout << "-- note: current iter is " << current_iter
                    << " with " << count_error.load(std::memory_order_relaxed) << " errors "
                    << count_collide.load(std::memory_order_relaxed) << " collides" << std::flush;
        }

        if (count_iter == max_iter) {
            std::cout << "\n";
        }
        std::cout << std::flush;
    }
};
#endif // BECC_USING_COUCHBASE_CXX_CLIENT

int main() {
#if BECC_USING_COUCHBASE_CXX_CLIENT
    // base data table
    BasicDbTable table;
    table.initialize_table_index();

    // prep atomic

    // prep iter

    // do start write
    {
    }

    // do start read
    {
    }

    // cleanup?
#endif // BECC_USING_COUCHBASE_CXX_CLIENT
    return 0;
}