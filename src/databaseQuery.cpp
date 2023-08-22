#include "databaseConnection.h"
#include <vector>
#include <map>

/**
 * @class DatabaseQuery
 * @brief Facilitates the execution of SQL queries and retrieval of results.
 * 
 * This class provides a utility to execute SQL queries on a connected database 
 * and return the results in a structured format.
 */
class DatabaseQuery {
private:
    DatabaseConnection dbConn;

public:

    /**
     * @brief Executes a provided SQL query and retrieves the results.
     * 
     * This method connects to the database, executes the given SQL query, and 
     * structures the results into a vector of maps where each map represents 
     * a row with column names as keys and their corresponding values.
     * 
     * @param query The SQL query string to be executed.
     * @return A vector of maps containing the result rows of the executed query.
     * If an SQL exception occurs, an empty vector is returned.
     */
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