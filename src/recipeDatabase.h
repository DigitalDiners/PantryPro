#ifndef RECIPE_DATABASE_H
#define RECIPE_DATABASE_H

#include "recipe.h"           // if the Recipe class is in its own file
#include "databaseConnection.h"
#include <string>

class RecipeDatabase {
private:
    DatabaseConnection dbConn;

public:
    Recipe getRecipeById(int id);
};

#endif  // RECIPE_DATABASE_H
