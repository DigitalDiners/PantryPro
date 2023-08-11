#include "dbconnection.h"
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

DBConnection::DBConnection() {
    boost::property_tree::ptree pt;

    try {
        boost::property_tree::ini_parser::read_ini("config.ini", pt);
    }
    catch (boost::property_tree::ini_parser::ini_parser_error& e) {
		std::cerr << "Error reading config.ini: " << e.what() << "\n";
		exit(1);
	}

    std::string server = pt.get<std::string>("database.server");
    std::string username = pt.get<std::string>("database.username");
    std::string password = pt.get<std::string>("database.password");

    driver = get_driver_instance();
    con = driver->connect(server, username, password);
}

DBConnection::~DBConnection() {
    delete con;
}

sql::Connection* DBConnection::getConnection() {
    return con;
}

