#include "databaseConnection.h"

/**
 * @brief Load database credentials from environment variables.
 * 
 * Private method to populate the uri, user, and password member variables.
 */
void DatabaseConnection::loadCredentialsFromENV() {
    const char* tempUri = std::getenv("DB_IP");
    const char* tempUser = std::getenv("DB_USER");
    const char* tempPass = std::getenv("DB_PASS");

    uri = (tempUri) ? tempUri : "";
    user = (tempUser) ? tempUser : "";
    password = (tempPass) ? tempPass : "";
}

/**
 * @brief Constructs a new DatabaseConnection object.
 * 
 * Initializes the SQL driver instance and loads the database credentials from environment variables.
 * Sets the default database name to "PantryPro".
 */
DatabaseConnection::DatabaseConnection() 
: driver(sql::mysql::get_driver_instance()) {
    loadCredentialsFromENV();
    database = "PantryPro";
}

/**
 * @brief Establishes and returns a connection to the database.
 * 
 * Uses the MySQL driver to connect using the loaded credentials. Sets the connection schema to 
 * the default database name.
 * 
 * @return A pointer to the established connection.
 */
std::unique_ptr<sql::Connection> DatabaseConnection::getConnection() {
    auto connection = std::unique_ptr<sql::Connection>(driver->connect(uri, user, password));
    connection->setSchema(database);
    return connection;
}
