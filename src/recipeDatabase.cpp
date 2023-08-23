<<<<<<< HEAD
=======
#include "recipeDatabase.h"
#include <iostream>
#include <vector>

Recipe RecipeDatabase::getRecipeById(int id) {
    std::string query = "SELECT * FROM recipes WHERE recipeId = " + std::to_string(id) + ";";

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        if (res->next()) {
            return Recipe(res->getInt("recipeId"), res->getString("recipeName"),
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

    return Recipe(0, "", 0, "", 0, 0, 0, "", "", "", 0, 0, 0);
}

<<<<<<< HEAD
>>>>>>> af16a1f (fixed Recipe for class)
=======
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
                    res->getString("reviewText"),
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

>>>>>>> 125ec19 (added feature to query reviews)
