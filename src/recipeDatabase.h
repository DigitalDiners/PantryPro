#ifndef RECIPE_DATABASE_H
#define RECIPE_DATABASE_H

#include "recipe.h"
#include "recipeImage.h"
#include "databaseConnection.h"
#include <string>

/**
 * @class RecipeDatabase
 * @brief Manages interactions between the application and the database for recipes.
 * 
 * The RecipeDatabase class provides methods to perform operations on recipes
 * stored in a database. It uses the DatabaseConnection class to establish and 
 * manage the database connection.
 */
class RecipeDatabase {
private:

    /** @brief Connection to the database. */
    DatabaseConnection dbConn;

public:

    /**
     * @brief Fetches a recipe from the database based on its unique identifier.
     * 
     * Queries the database for a recipe with the given ID. If found, constructs a Recipe object
     * with the relevant data and returns it. In the case of a SQL exception, an error message is printed
     * to the console. If no recipe matches the ID or there's an exception, a default Recipe object is returned.
     * 
     * @param id The unique identifier of the recipe to fetch.
     * @return The Recipe object corresponding to the given ID or a default Recipe object if not found.
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
};

#endif  // RECIPE_DATABASE_H
