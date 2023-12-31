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
            return Recipe(res->getInt("recipeId"), 
            res->getString("recipeName"),
                            res->getInt("authorId"),
                            res->getInt("cookTime"), 
                            res->getInt("prepTime"), 
                            res->getInt("totalTime"),
                            res->getString("datePublished"), 
                            res->getString("description"), 
                            res->getString("category"),
                            res->getInt("calories"), 
                            res->getInt("servings"), 
                            res->getInt("yieldQuantity"), 
                            res->getString("instructions"));
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

std::vector<int> RecipeDatabase::getFeaturedRecipes(){
    std::vector<int> results;

    std::cout<<"get featured form database called"<<std::endl;

    std::string query =  "SELECT recipes.* FROM recipes, reviews WHERE recipes.recipeId IN (SELECT DISTINCT recipeId FROM images) AND recipes.`recipeId` = reviews.`recipeId` AND reviews.rating = 5 AND recipes.category NOT LIKE 'Beverages' ORDER BY `datePublished` DESC LIMIT 100;";



    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

        while (res->next()) {
            results.push_back(res->getInt("recipeId"));
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    return results;

}

std::vector<Recipe> RecipeDatabase::getRecipesBySearch(const std::vector<std::string> &ingredients) {
    std::vector<Recipe> result;
    
    if (ingredients.empty()) {
        return result; 
    }

    std::string baseQuery = 
        "SELECT recipes.* "
        "FROM recipes "
        "JOIN recipe_ingredients ON recipes.recipeId = recipe_ingredients.recipeId "
        "JOIN ingredients ON recipe_ingredients.ingredientId = ingredients.ingredientId "
        "WHERE recipes.recipeId IN (SELECT DISTINCT recipeId FROM images) AND (";

    std::string havingClause = ") GROUP BY recipes.recipeId HAVING ";

    for (size_t i = 0; i < ingredients.size(); ++i) {
        baseQuery += "ingredients.name LIKE '%" + ingredients[i] + "%' ";
        havingClause += "SUM(ingredients.name LIKE '%" + ingredients[i] + "%') > 0 ";
        if (i < ingredients.size() - 1) {
            baseQuery += "OR ";
            havingClause += "AND ";
        }
    }
    baseQuery += havingClause;
    baseQuery += " ORDER BY recipes.datePublished DESC LIMIT 50;";

    
    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(baseQuery));

        while (res->next()) {
            result.push_back(Recipe(res->getInt("recipeId"), 
                                    res->getString("recipeName"),
                                    res->getInt("authorId"),
                                    res->getInt("cookTime"), 
                                    res->getInt("prepTime"), 
                                    res->getInt("totalTime"),
                                    res->getString("datePublished"), 
                                    res->getString("description"), 
                                    res->getString("category"),
                                    res->getInt("calories"), 
                                    res->getInt("servings"), 
                                    res->getInt("yieldQuantity"), 
                                    res->getString("instructions")));
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

std::vector<Review> RecipeDatabase::getAllReviewsForRecipes(const std::vector<Recipe>& recipes) {

    std::vector<Review> reviewVector;

    if (recipes.empty())
       { return reviewVector;}


    std::stringstream query;
    query << "SELECT * FROM reviews WHERE recipeId IN(";

    bool isFirst = true;
    for (const Recipe &recipe : recipes)
    {
        if (!isFirst) query << ",";
        isFirst = false;
        query << recipe.getId();
    }
    query << ") ;";

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query.str()));

        while (res->next()) 
        {
                Review review(
                    res->getInt("reviewId"),
                    res->getInt("recipeId"),
                    res->getInt("authorId"),
                    res->getInt("rating"),
                    res->getString("review"),
                    res->getString("dateSubmitted"),
                    res->getString("dateModified")
                );
            reviewVector.push_back(review);
        }
    }catch (sql::SQLException &e)
    {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return reviewVector;
}

std::map<int, std::vector<Ingredient>> RecipeDatabase::getIngredientsForRecipes(const std::vector<int>& recipeIds) {
    std::map<int, std::vector<Ingredient>> ingredientsMap;

    if (recipeIds.empty()) {
        return ingredientsMap;
    }

    std::stringstream query;
    query << 
        "SELECT ingredients.name, ingredients.ingredientId, recipe_ingredients.recipeId "
        "FROM recipe_ingredients JOIN ingredients "
        "ON recipe_ingredients.ingredientId = ingredients.ingredientId "
        "WHERE recipe_ingredients.recipeId IN (";

    for (size_t i = 0; i < recipeIds.size(); ++i) {
        query << recipeIds[i];
        if (i < recipeIds.size() - 1) {
            query << ",";
        }
    }
    query << ");";

    try {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query.str()));

        while (res->next()) {
            int recipeId = res->getInt("recipeId");
            Ingredient ingredient(
                res->getInt("ingredientId"),
                res->getString("name")
            );
            ingredientsMap[recipeId].push_back(ingredient);
        }
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return ingredientsMap;
}

std::vector<RecipeImage> RecipeDatabase::getAllRecipeImagesForRecipes(const std::vector<Recipe>& recipes)
{
    std::vector<RecipeImage> resultVector;

    if (recipes.empty())
        return resultVector;

    std::stringstream query;
    query << "SELECT * FROM images WHERE recipeId IN (";

    bool isFirst = true;
    for (const Recipe &recipe : recipes)
    {
        if (!isFirst) query << ",";
        isFirst = false;
        query << recipe.getId();
    }
    query << ") and imageNumber = 1;";

    try
    {
        auto con = dbConn.getConnection();
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query.str()));

        while (res->next())
        {
            RecipeImage image(res->getInt("recipeId"),
                              res->getInt("imageNumber"),
                              res->getString("imageURL"));
            resultVector.push_back(image);
        }
    }
    catch (sql::SQLException &e)
    {
        std::cout << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return resultVector;
}



