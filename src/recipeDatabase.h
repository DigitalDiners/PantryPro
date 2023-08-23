#ifndef recipe_DATABASE_H
#define recipe_DATABASE_H

#include "recipe.h"           // if the recipe class is in its own file
#include "databaseConnection.h"
#include <string>

/**
 * @class recipeDatabase
 * @brief Manages interactions between the application and the database for recipes.
 * 
 * The recipeDatabase class provides methods to perform operations on recipes
 * stored in a database. It uses the DatabaseConnection class to establish and 
 * manage the database connection.
 */
class recipeDatabase {
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
    recipe getrecipeById(int id);
};

#endif  // recipe_DATABASE_H
