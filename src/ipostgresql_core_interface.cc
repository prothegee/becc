#include <becc/interfaces/ipostgresql_core_interface.hh>

#include <iostream>

namespace becc
{
#if BECC_USING_POSTGRESQL
IPostgreSqlCoreInterface::_IPostgreSQL::~_IPostgreSQL()
{
    if (m_pConn != nullptr) { PQfinish(m_pConn); }
}

int32_t IPostgreSqlCoreInterface::_IPostgreSQL::initialize_database(const postgresql_connection_t &connection_data, const bool &create_db)
{
    IPostgreSqlCoreInterface::m_connection.dbname = connection_data.dbname;
    IPostgreSqlCoreInterface::m_connection.host = connection_data.host;
    IPostgreSqlCoreInterface::m_connection.port = connection_data.port;
    IPostgreSqlCoreInterface::m_connection.username = connection_data.username;
    IPostgreSqlCoreInterface::m_connection.password = connection_data.password;

    std::string conninfo;

    try
    {
        if (create_db)
        {
            if (connection_data.password.length() <= 0)
            {
                conninfo = "user=" + connection_data.username + " host=" + connection_data.host + " port=" + connection_data.port;
            }
            else
            {
                conninfo = "user=" + connection_data.username + " host=" + connection_data.host + " port=" + connection_data.port + " password=" + connection_data.password;
            }

            PGresult *pRes = nullptr;

            m_pConn = PQconnectdb(conninfo.c_str());

            if (PQstatus(m_pConn) != CONNECTION_OK)
            {
                std::cerr << "ERROR: postgresql connection error, check your config\n";
                abort();
            }
            else
            {
                std::string query = "create database " + connection_data.dbname + ";";

                pRes = PQexec(m_pConn, query.c_str());

                if (PQresultStatus(pRes) != PGRES_COMMAND_OK)
                {
                    std::cerr << PQerrorMessage(m_pConn) << "\n";
                }
                else
                {
                    #if BECC_IS_DEBUG
                    std::cout << "DEBUG: database created\n";
                    #endif // BECC_IS_DEBUG
                }
            }

            if (pRes != nullptr) { PQclear(pRes); }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -69;
    }

    return 0;
}

std::string IPostgreSqlCoreInterface::_IPostgreSQL::generate_uuid_v1_as_string()
{
    std::string result = "";

    PGresult *pPgRes = nullptr;

    if (PQstatus(m_pConn) == CONNECTION_OK)
    {
        pPgRes = PQexec(m_pConn, "SELECT uuid_generate_v1();");
        result = PQgetvalue(pPgRes, 0, 0);
    }
    else
    {
        std::cerr << "ERROR: connection to database failed: " << PQerrorMessage(m_pConn) << "\n";
    }

    PQclear(pPgRes);

    return result;
}

std::string IPostgreSqlCoreInterface::_IPostgreSQL::generate_uuid_v4_as_string()
{
    std::string result = "";

    PGresult *pPgRes = nullptr;

    if (PQstatus(m_pConn) == CONNECTION_OK)
    {
        pPgRes = PQexec(m_pConn, "SELECT uuid_generate_v4();");
        result = PQgetvalue(pPgRes, 0, 0);
    }
    else
    {
        std::cerr << "ERROR: connection to database failed: " << PQerrorMessage(m_pConn) << "\n";
    }

    PQclear(pPgRes);

    return result;
}
#endif // BECC_USING_POSTGRESQL
} // namespace becc
