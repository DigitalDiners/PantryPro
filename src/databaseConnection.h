#pragma once

#include <string>
#include <memory>
#include <mysql/jdbc.h>

/**
 * @class DatabaseConnection
 * @brief Manages database connections using MySQL.
 * 
 * This class is responsible for establishing and returning MySQL connections. 
 * It loads credentials from environment variables to facilitate connections.
 */
class DatabaseConnection {
private:
    std::string uri;
    std::string user;
    std::string password;
    std::string database;
    sql::Driver* driver;

    /**
     * @brief Load database credentials from environment variables.
     * 
     * This method reads the DB_IP, DB_USER, and DB_PASS environment variables 
     * to set the uri, user, and password members, respectively.
     */
    void loadCredentialsFromENV();

public:

    /**
     * @brief Default constructor.
     * 
     * Instantiates the DatabaseConnection object and loads credentials from environment variables.
     * Also initializes the database name as "PantryPro".
     */
    DatabaseConnection();

    /**
     * @brief Establishes and returns a connection to the database.
     * 
     * Uses the MySQL driver to connect using the loaded credentials. Sets the connection schema to 
     * the default database name.
     * 
     * @return A pointer to the established connection.
     */
    std::unique_ptr<sql::Connection> getConnection();
};
