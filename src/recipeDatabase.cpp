#include "recipeDatabase.h"
#include <iostream>

recipe recipeDatabase::getrecipeById(int id) {
    std::string query = "SELECT * FROM recipes WHERE recipeId = " + std::to_string(id) + ";";

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        if (res->next()) {
            return recipe(res->getInt("recipeId"), res->getString("recipeName"),
                            res->getInt("authorId"), res->getString("authorName"),
                            res->getInt("cookTime"), res->getInt("prepTime"), res->getInt("totalTime"),
                            res->getString("datePublished"), res->getString("description"), res->getString("category"),
                            res->getInt("calories"), res->getInt("servings"), res->getInt("yieldQuantity"));
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return recipe(0, "", 0, "", 0, 0, 0, "", "", "", 0, 0, 0);
}

