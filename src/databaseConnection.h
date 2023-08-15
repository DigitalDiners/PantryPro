#pragma once

#include <string>
#include <memory>
#include <mysql/jdbc.h>

class DatabaseConnection {
private:
    std::string uri;
    std::string user;
    std::string password;
    std::string database;
    sql::Driver* driver;

    void loadCredentialsFromINI();

public:
    DatabaseConnection();
    std::unique_ptr<sql::Connection> getConnection();
};
