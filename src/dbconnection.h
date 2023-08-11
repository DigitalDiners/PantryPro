#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/sqlstring.h>
#include <cppconn/prepared_statement.h>

class DBConnection {
public:
    DBConnection();
    ~DBConnection();
    sql::Connection* getConnection();

private:
    sql::Driver* driver;
    sql::Connection* con;
};

#endif // DBCONNECTION_H
