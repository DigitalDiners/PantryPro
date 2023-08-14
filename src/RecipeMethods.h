#ifndef RECIPE_METHODS_H
#define RECIPE_METHODS_H

#include <vector>
#include "Recipe.h"
#include "Ingredients.h"

std::vector<Recipe> filterRecipesByIngredients(const std::vector<Recipe>& allRecipes, const std::vector<Ingredients>& ingredients);
void addRecipe(std::vector<Recipe>& recipes, const Recipe& newRecipe, const std::string& filename);
vector<Recipe> editRecipe(std::vector<Recipe>& recipes, const Recipe& oldRecipe, const Recipe& changedRecipe, const std::string& filename);

#endif
