#include <becc/becc.hh>

#if BECC_USING_SCYLLADB
#include <becc/functions/date_and_time.hh>
#include <becc/functions/utility.hh>
#include <becc/interfaces/iscylladb_core_interface.hh>

#include <mutex>
#include <thread>
#include <future>
#include <chrono>
#include <iostream>
#include <atomic>

// main config file for this test
// if doesn't exists, copy the "test_database_scylla_rw.json.debug" and rename to "test_database_scylla_rw.json"
INLNSTTCCNST std::string CONFIG_FILE = "../../../tests/test_database_scylla_rw.json";

std::mutex print_mutex;
class BasicDbTable : public becc::IScyllaDbCoreInterface {
private:
    becc::scylladb_connection_t m_conn; // connection data

public:
    INLNSTTCCNST std::string TABLE_NAME = "test_rw";

    INLNSTTCCNST std::string TABLE_GEN_1ST = R"(
create table if not exists {KEYSPACE}.{TABLE_NAME} (
    id                  uuid,
    random_text         text,
    random_integer      int,
    random_big_integer  bigint,
    random_float        float,
    random_double       double,
    created_timestamp   timestamp,
    created_timestring  text,

    primary key (id)
);
    )";

    /////////////////////////////////////////////////////////////////

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

    BasicDbTable() {
        const auto CONFIG = becc::utility_functions::jsoncpp::from_json_file(CONFIG_FILE);

        const int32_t CONN_AUTH = CONFIG["becc_test_scylladb"]["connection"]["auth"].asInt();

        becc::scylladb_connection_t conn;

        conn.auth_mode = (becc::scylladb_auth_mode_e)CONN_AUTH;

        conn.host.clear();
        for (auto& host : CONFIG["becc_test_scylladb"]["connection"]["hosts"]) {
            auto this_host = host.asString() + ",";
            conn.host += this_host;
        }
        conn.host.resize(conn.host.size() - 1); // remove last , (coma)

        conn.username = CONFIG["becc_test_scylladb"]["connection"]["username"].asString();
        conn.password = CONFIG["becc_test_scylladb"]["connection"]["password"].asString();

        conn.keyspace = CONFIG["becc_test_scylladb"]["keyspace"].asString();
        conn.strategy = (becc::scylladb_topology_strat_e)CONFIG["becc_test_scylladb"]["strategy"].asInt();

        conn.multiple_datacenters = CONFIG["becc_test_scylladb"]["multiple_datacenters"].asBool();

        conn.factors_configs = CONFIG["becc_test_scylladb"]["factors_configs"][CONN_AUTH][0].asString();
        conn.factors_configs_extra = CONFIG["becc_test_scylladb"]["factors_configs_extra"].asString();

        IScyllaDb.initialize_constructor(conn);

        // // check table gen
        // std::cout << "table gen: " << TABLE_GEN_1ST << "\n";

        // finally
        m_conn = conn;
    }
    ~BasicDbTable() {};

    void initialize() {
        // create keyspace if not exists
        //
        std::string query = "create keyspace if not exists {KEYSPACE} with replication = { 'class': '{TOPOLOGY_STRATEGY}' };";

        becc::utility_functions::find::and_replace_all(query, "{KEYSPACE}", m_conn.keyspace);
        becc::utility_functions::find::and_replace_all(query, "{TOPOLOGY_STRATEGY}", becc::scylladb_topology_strat_to_string(m_conn.strategy));

        std::string note = "creating keypace " + m_conn.keyspace;

        if (IScyllaDb.execute_cqlsh(IScyllaDb.get_cass_session(), query.c_str(), note.c_str()) != CASS_OK) {
            note += "fail! @";
            note += std::string(__FILE__);
            note += " ";
            note += std::to_string(__LINE__);
            IScyllaDb.print_error(
                IScyllaDb.get_cass_future(), note.c_str()
            );
        }

        cleanup();
    }

    void initialize_table() {
        std::string query = TABLE_GEN_1ST;

        becc::utility_functions::find::and_replace_all(query, "{KEYSPACE}", m_conn.keyspace);
        becc::utility_functions::find::and_replace_all(query, "{TABLE_NAME}", TABLE_NAME);

        if (IScyllaDb.execute_cqlsh(IScyllaDb.get_cass_session(), query.c_str(), "BasicDbTable::initialize_table") != CASS_OK) {
            IScyllaDb.print_error(
                IScyllaDb.get_cass_future()
            );
        }
    }

    void initialize_table_index() {
        /* not implemented */
    }

    void initialize_table_materialized_view() {
        /* not implemented */
    }

    void initialize_table_and_alterize_table() {
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

        std::string query = R"(insert into {KEYSPACE}.{TABLE_NAME} (
    id, random_text,
    random_integer, random_big_integer,
    random_float, random_double,
    created_timestamp, created_timestring
) values (
    ?, ?,
    ?, ?,
    ?, ?,
    ?, ?
); -- don't use if not exists
)";
        becc::utility_functions::find::and_replace_all(query, "{KEYSPACE}", m_conn.keyspace);
        becc::utility_functions::find::and_replace_all(query, "{TABLE_NAME}", TABLE_NAME);

        size_t query_params = 8;

        CassFuture *p_future = nullptr;
        CassStatement *p_statement = cass_statement_new(query.c_str(), query_params);

        // id
        CassUuid id = IScyllaDb.convert_string_to_uuid(data.id);
        cass_statement_bind_uuid(p_statement, 0, id);
        // random_text
        cass_statement_bind_string(p_statement, 1, data.random_text.c_str());
        // random_integer
        cass_statement_bind_int32(p_statement, 2, data.random_integer);
        // random_big_integer
        cass_statement_bind_int64(p_statement, 3, data.random_big_integer);
        // random_float
        cass_statement_bind_float(p_statement, 4, data.random_float);
        // random_double
        cass_statement_bind_double(p_statement, 5, data.random_double);
        // created_timestamp
        cass_statement_bind_int64(p_statement, 6, data.created_timestamp);
        // created_timestring
        cass_statement_bind_string(p_statement, 7, data.created_timestring.c_str());

        p_future = cass_session_execute(IScyllaDb.get_cass_session(), p_statement);
        cass_future_wait(p_future);

        if (cass_future_error_code(p_future) != CASS_OK) {
            IScyllaDb.print_error(p_future);
            count_error.fetch_add(1, std::memory_order_relaxed);
            // count_error += 1;
            // colide should be check for the primary key, do it later or never
        }

        uint64_t current_iter = count_iter.fetch_add(1, std::memory_order_relaxed) + 1;

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

        cass_future_free(p_future);
        cass_statement_free(p_statement);
    }

    // this function will:
    // - drop this class table if exists
    void cleanup() {
        std::string query = "drop table if exists {KEYSPACE}.{TABLE_NAME};";

        becc::utility_functions::find::and_replace_all(query, "{KEYSPACE}", m_conn.keyspace);
        becc::utility_functions::find::and_replace_all(query, "{TABLE_NAME}", TABLE_NAME);

        if (IScyllaDb.execute_cqlsh(IScyllaDb.get_cass_session(), query.c_str(), "BasicDbTable::cleanup") != CASS_OK) {
            IScyllaDb.print_error(
                IScyllaDb.get_cass_future(), "BasicDbTable::cleanup: can't drop the table"
            );
        }
    }
}; // class SyllaDbRW

#endif // BECC_USING_SCYLLADB

int main() {
#if BECC_USING_SCYLLADB
    // base data table
    BasicDbTable table;
    table.initialize();
    table.initialize_table();
    table.initialize_table_index();
    table.initialize_table_materialized_view();
    table.initialize_table_and_alterize_table();

    std::atomic<uint64_t> count_iter(0), count_error(0), count_collide(0);

    const uint64_t MAX_ITER_WRITE = 100;
    // const uint64_t MAX_ITER_READ = 100;
    // const uint64_t NUM_THREADS = std::thread::hardware_concurrency();

    std::cout << "start write\n";
    {
        std::vector<std::future<void>> futures;

        auto start = std::chrono::high_resolution_clock::now();

        futures.reserve(MAX_ITER_WRITE);

        for (uint64_t i = 0; i < MAX_ITER_WRITE; ++i) {
            futures.push_back(std::async(
                std::launch::async,
                [&table, &count_error, &count_iter, &count_collide, &MAX_ITER_WRITE]() {
                    table.generate_random_data(count_error, count_iter, count_collide, MAX_ITER_WRITE);
                }
            ));
        }

        for (auto& future : futures) {
            future.get();
        }

        //
        /*
        - for 100 with get   : 0.199751 seconds
        - for 100 without get: 0.00568378 seconds
        */
        //

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float64_t> duration = end - start;

        uint64_t errors = count_error.load();
        uint64_t collides = count_collide.load();

        if (errors > 0 || count_collide > 0)
        {
            std::cout << "\n-- note: found " << errors << " error & " << collides << " collide, while executing in " << duration.count() << "seconds\n";
        }
        else
        {
            std::cout << "\n-- note: no error & collide found in " << duration.count() << " seconds\n";
        }
    }

    std::cout << "skipped: start read\n";
    {
        // tba
    }

    // finally
    table.cleanup();
#endif // BECC_USING_SCYLLADB
    return 1;
}