#include "MyApp.h"
#include "databaseConnection.h"

int main(){

    DatabaseConnection dbConn;

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT 'Welcome to Connector/C++' AS _message"));

        while (res->next()) {
            std::cout << "MySQL replies: " << res->getString("_message") << std::endl;
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return EXIT_FAILURE;
    }

    MyApp app;
    app.Run();

    return 0;
}
