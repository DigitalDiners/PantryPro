#pragma once

#include <string>
#include <memory>
#include <mysql/jdbc.h>
#include <vector>

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
     * Private method to populate the uri, user, and password member variables.
     */
    void loadCredentialsFromENV();

public:

    /**
     * @brief Constructs a new DatabaseConnection object.
     * 
     * Initializes the SQL driver instance and loads the database credentials from environment variables.
     * Sets the default database name to "PantryPro".
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
