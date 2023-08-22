#include "databaseConnection.h"

void DatabaseConnection::loadCredentialsFromENV() {
    const char* tempUri = std::getenv("DB_IP");
    const char* tempUser = std::getenv("DB_USER");
    const char* tempPass = std::getenv("DB_PASS");

    uri = (tempUri) ? tempUri : "";
    user = (tempUser) ? tempUser : "";
    password = (tempPass) ? tempPass : "";
}

DatabaseConnection::DatabaseConnection() 
: driver(sql::mysql::get_driver_instance()) {
    loadCredentialsFromENV();
    database = "PantryPro";
}

std::unique_ptr<sql::Connection> DatabaseConnection::getConnection() {
    auto connection = std::unique_ptr<sql::Connection>(driver->connect(uri, user, password));
    connection->setSchema(database);
    return connection;
}
