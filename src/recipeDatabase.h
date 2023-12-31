#ifndef RECIPE_DATABASE_H
#define RECIPE_DATABASE_H

#include "recipe.h"
#include "recipeImage.h"
#include "review.h"
#include "databaseConnection.h"
#include <string>
#include <sstream>
#include "ingredient.h"

/**
 * @class recipeDatabase
 * @brief Manages interactions between the application and the database for recipes.
 *
 * The recipeDatabase class provides methods to perform operations on recipes
 * stored in a database. It uses the DatabaseConnection class to establish and
 * manage the database connection.
 */
class RecipeDatabase
{
private:
    /** @brief Connection to the database. */
    DatabaseConnection dbConn;

public:
    /**
     * @brief Fetches a recipe from the database based on its unique identifier.
     *
     * Queries the database for a recipe with the given ID. If found, constructs a recipe object
     * with the relevant data and returns it. In the case of a SQL exception, an error message is printed
     * to the console. If no recipe matches the ID or there's an exception, a default recipe object is returned.
     *
     * @param id The unique identifier of the recipe to fetch.
     * @return The recipe object corresponding to the given ID or a default recipe object if not found.
     */
    Recipe getRecipeById(int id);

    /**
     * @brief Get the Recipe Image By Id object
     *
     * @param id The unique identifier of the recipe to fetch the image from.
     * @param imageNumber The image number of the recipe image to fetch from a given recipe.
     * @return The RecipeImage object corresponding to the given ID or a default RecipeImage object if not found.
     */
    RecipeImage getRecipeImage(int id, int imageNumber);

    /**

     * @brief Construct a new Recipe Database::get Recipes By Search object
     *
     * @param search
     */
    std::vector<Recipe> getRecipesBySearch(const std::vector<std::string> &ingredients);

    /**

     * @brief Get the Reviews By Recipe Id object
     *
     * @param recipeId The unique identifier of the recipe to fetch the reviews from.
     * @return A vector of Review objects corresponding to the given recipe ID or an empty vector if not found.
     */
    std::vector<Review> getReviewsByRecipeId(int recipeId);

    /**

     * @brief Get a list of Ingredients By Recipe Id
     *
     * @param recipeId The unique identifier of the recipe to fetch the ingredients from.
     * @return A vector of Ingredient objects corresponding to the given recipe ID or an empty vector if not found.
     */
    std::map<int, std::vector<Ingredient>> getIngredientsForRecipes(const std::vector<int> &recipeIds);

    std::vector<RecipeImage> getAllRecipeImagesForRecipes(const std::vector<Recipe> &recipes);

    std::vector<Review> getAllReviewsForRecipes(const std::vector<Recipe> &recipes);

    std::vector<int> getFeaturedRecipes();
};

#endif // recipe_DATABASE_H
