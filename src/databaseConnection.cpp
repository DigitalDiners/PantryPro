#include "databaseConnection.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

void DatabaseConnection::loadCredentialsFromINI() {
    boost::property_tree::ptree pt;
    
    boost::property_tree::ini_parser::read_ini("../../../../config.ini", pt);

    uri = pt.get<std::string>("database.url");
    user = pt.get<std::string>("database.username");
    password = pt.get<std::string>("database.password");
    database = pt.get<std::string>("database.database_name");
}

DatabaseConnection::DatabaseConnection() 
: driver(sql::mysql::get_driver_instance()) {
    loadCredentialsFromINI();
}

std::unique_ptr<sql::Connection> DatabaseConnection::getConnection() {
    auto connection = std::unique_ptr<sql::Connection>(driver->connect(uri, user, password));
    connection->setSchema(database);
    return connection;
}
