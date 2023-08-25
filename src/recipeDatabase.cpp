#include "recipeDatabase.h"
#include <iostream>

Recipe RecipeDatabase::getRecipeById(int id) {
    std::string query = "SELECT * FROM recipes WHERE recipeId = " + std::to_string(id) + ";";

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        if (res->next()) {
            return Recipe(res->getInt("recipeId"), res->getString("recipeName"),
                            res->getInt("authorId"),
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

    return Recipe(0, "", 0, 0, 0, 0, "", "", "", 0, 0, 0);
}

RecipeImage RecipeDatabase::getRecipeImage(int id, int imageNumber) {
    std::string query = "SELECT * FROM images WHERE recipeId = " + std::to_string(id) + " and imageNumber = " + std::to_string(imageNumber) + ";";

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        if (res->next()) {
            return RecipeImage(res->getInt("recipeId"), res->getInt("imageNumber"), res->getString("imageURL"));
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return RecipeImage(0, 0, "");
}

std::vector<Recipe> RecipeDatabase::getRecipesBySearch(const std::string &search) {
    std::vector<Recipe> result;

    // Split search string into individual words
    std::stringstream ss(search);
    std::string word;
    std::vector<std::string> words;

    while (ss >> word) {
        words.push_back(word);
    }

    if (words.empty()) {
        return result; // empty list
    }

    // Construct SQL query using the LIKE operator for each word
    std::string query = "SELECT * FROM recipes WHERE ";
    for (size_t i = 0; i < words.size(); ++i) {
        query += "recipeName LIKE '%" + words[i] + "%'";

        if (i < words.size() - 1) {
            query += " OR ";
        }
    }
    query += " LIMIT 10;";

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        while (res->next()) {
            result.push_back(Recipe(res->getInt("recipeId"), res->getString("recipeName"),
                                    res->getInt("authorId"),
                                    res->getInt("cookTime"), res->getInt("prepTime"), res->getInt("totalTime"),
                                    res->getString("datePublished"), res->getString("description"), res->getString("category"),
                                    res->getInt("calories"), res->getInt("servings"), res->getInt("yieldQuantity")));
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    std::cout << "Number of results: " << result.size() << std::endl;
    std::cout << "First result: " << result[0].getName() << std::endl;
    std::cout << "Second result: " << result[1].getName() << std::endl;
    std::cout << "Third result: " << result[2].getName() << std::endl;

    return result;
}


