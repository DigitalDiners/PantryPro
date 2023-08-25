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

std::vector<Recipe> RecipeDatabase::getRecipesBySearch(const std::vector<std::string> &ingredients) {
    std::vector<Recipe> result;

    if (ingredients.empty()) {
        return result; // empty list
    }

    // Construct SQL query using JOIN and LIKE operator for each ingredient
    std::string query = "SELECT recipes.* FROM recipes ";
    
    for (size_t i = 0; i < ingredients.size(); ++i) {
        query += "JOIN recipe_ingredients AS ri" + std::to_string(i) + " ON recipes.recipeId = ri" + std::to_string(i) + ".recipeId ";
        query += "JOIN ingredients AS ing" + std::to_string(i) + " ON ri" + std::to_string(i) + ".ingredientId = ing" + std::to_string(i) + ".ingredientId AND ing" + std::to_string(i) + ".name LIKE '%" + ingredients[i] + "%' ";
    }

    query += "GROUP BY recipes.recipeId HAVING COUNT(DISTINCT recipes.recipeId) = " + std::to_string(ingredients.size()) + " LIMIT 20;";

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

    return result;
}




