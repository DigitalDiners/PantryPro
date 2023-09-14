#include "recipeDatabase.h"
#include <iostream>
#include <vector>
#include <string>

Recipe RecipeDatabase::getRecipeById(int id) {
    std::string query = "SELECT r.*,  i.imageURL , i.`imageNumber` FROM recipes AS r JOIN images AS i WHERE r.`recipeId`=" + std::to_string(id) + " AND i.`recipeId`= " + std::to_string(id) + ";" ;
    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        if (res->next()) {
            return Recipe(res->getInt("recipeId"), res->getString("recipeName"),
                            res->getInt("authorId"),
                            res->getInt("cookTime"), res->getInt("prepTime"), res->getInt("totalTime"),
                            res->getString("datePublished"), res->getString("description"), res->getString("category"),
                            res->getInt("calories"), res->getInt("servings"), res->getInt("yieldQuantity"), res->getString("instructions"));
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return Recipe(0, "", 0, 0, 0, 0, "", "", "", 0, 0, 0, "");
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

std::vector<std::string> RecipeDatabase::getIngredients(int &recipeId, std::vector<std::string> have){
    std::vector<std::string> need;
    std::cout<<recipeId<<std::endl;
    std::string query = "SELECT i.name FROM recipes AS r, ingredients AS i, recipe_ingredients  WHERE r.recipeId=recipe_ingredients.recipeId AND i.ingredientId = recipe_ingredients.ingredientId AND r.`recipeId`=" + std::to_string(recipeId) + ";";

    for (const std::string& thing : have) {
        std::cout << thing << std::endl;
    }
        try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        while (res->next()) {
            need.push_back(     
                res->getString("name")
            );
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    for (const std::string& thing : need) {
        std::cout << thing << "+"<<std::endl;
    }

     // Sort the vectors for efficient comparison
    std::sort(have.begin(), have.end());
    std::sort(need.begin(), need.end());

    // Find the missing ingredients using set_difference
    std::vector<std::string> missing;
    std::set_difference(need.begin(), need.end(), have.begin(), have.end(), std::back_inserter(missing));

    // Print the missing ingredients
    if (missing.empty()) {
        std::cout << "You have all the ingredients you need." << std::endl;
    } else {
        std::cout << "You need the following ingredients: ";
        for (const std::string& ingredient : missing) {
            std::cout << ingredient << " ";
        }
        std::cout << std::endl;
    }
    return missing;
}

std::vector<Recipe> RecipeDatabase::getRecipesBySearch(const std::vector<std::string> &ingredients) {
    std::vector<Recipe> result;

    if (ingredients.empty()) {
        return result;
    }

    std::string query = "SELECT recipes.* FROM recipes ";
    query += "JOIN recipe_ingredients ON recipes.recipeId = recipe_ingredients.recipeId ";
    query += "JOIN ingredients ON recipe_ingredients.ingredientId = ingredients.ingredientId WHERE ";

    for (size_t i = 0; i < ingredients.size(); i++) {
        query += "ingredients.name LIKE ?";
        if (i != ingredients.size() - 1) {
            query += " OR ";
        }
    }
    
    query += " GROUP BY recipes.recipeId ";
    query += "HAVING COUNT(DISTINCT ingredients.name) = ? ";
    query += "LIMIT 20;";

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(query));

        for (size_t i = 0; i < ingredients.size(); i++) {
            pstmt->setString(i + 1, "%" + ingredients[i] + "%");
        }
        pstmt->setInt(ingredients.size() + 1, ingredients.size());

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            result.push_back(Recipe(res->getInt("recipeId"), res->getString("recipeName"),
                                    res->getInt("authorId"),
                                    res->getInt("cookTime"), res->getInt("prepTime"), res->getInt("totalTime"),
                                    res->getString("datePublished"), res->getString("description"), res->getString("category"),
                                    res->getInt("calories"), res->getInt("servings"), res->getInt("yieldQuantity"), res->getString("instructions")));
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return result;
}


std::vector<Review> RecipeDatabase::getReviewsByRecipeId(int recipeId) {
    std::vector<Review> reviews;

    std::string query = "SELECT * FROM reviews WHERE recipeId = " + std::to_string(recipeId) + ";";

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        while (res->next()) {
            reviews.push_back(
                Review(
                    res->getInt("reviewId"),
                    res->getInt("recipeId"),
                    res->getInt("authorId"),
                    res->getInt("rating"),
                    res->getString("review"),
                    res->getString("dateSubmitted"),
                    res->getString("dateModified")
                )
            );
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return reviews;
}

