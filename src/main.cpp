#include "MyApp.h"
#include "databaseConnection.h"

int main()
{

    // Example of using the database connection and querying the database (can be deleted)
    DatabaseConnection dbConn;
    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("USE PantryPro;");
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM recipes;"));
        while (res->next()){
            std::cout << "Recipe Name: " << res->getString("recipeName") << std::endl;
        }
    } catch (sql::SQLException &e){
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
