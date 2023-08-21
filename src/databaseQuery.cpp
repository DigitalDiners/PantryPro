#include "databaseConnection.h"
#include <vector>
#include <map>

// This class can be used to perform general queries to the database
class DatabaseQuery {
private:
    DatabaseConnection dbConn;

public:
    // This method returns a vector of maps. Each map represents a row in the result set.
    std::vector<std::map<std::string, std::string>> executeQuery(const std::string& query) {
        std::vector<std::map<std::string, std::string>> results;
        
        try {
            auto con = dbConn.getConnection();
            std::unique_ptr<sql::Statement> stmt(con->createStatement());
            stmt->execute("USE PantryPro;");
            std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

            while (res->next()){
                std::map<std::string, std::string> row;
                sql::ResultSetMetaData* metaData = res->getMetaData();
                for (size_t i = 1; i <= metaData->getColumnCount(); ++i) {
                    row[metaData->getColumnName(i)] = res->getString(i);
                }
                results.push_back(row);
            }
        } catch (sql::SQLException &e){
            std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            return std::vector<std::map<std::string, std::string>>();
        }
        return results;
    }
};