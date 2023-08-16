#include "Recipe.h"

using namespace std;


/**
 * setting methods to create or edit recipes
*/

void Recipe::setRecipeID(int id) {
    recipeID = id;
}

void Recipe::setRecipeName(const std::string& name) {
    recipeName = name;
}

void Recipe::setPrepTime(const std::string& prep) {
    prepTime = prep;
}

void Recipe::setTotalTime(const std::string& total) {
    totalTime = total;
}

void Recipe::setCategory(const std::string& cat) {
    category = cat;
}

void Recipe::setCalories(float cal) {
    calories = cal;
}

void Recipe::addIngredient(const Ingredients& ingredient) {
    ingredients.push_back(ingredient);
}



/**
 * getting methods to get all parts of each recipe
 */
int Recipe::getRecipeID(Recipe recipe) { 
    return recipe.recipeID; 
}
    
string Recipe::getRecipeName(Recipe recipe) { 
    return recipe.recipeName; 
}
    
string Recipe::getPrepTime(Recipe recipe) { 
    return recipe.prepTime; 
}
    
string Recipe::getTotalTime(Recipe recipe) { 
    return recipe.totalTime; 
}

string Recipe::getCategory(Recipe recipe) {
     return recipe.category; 
}

float Recipe::getCalories(Recipe recipe) { 
    return recipe.calories; 
}

const vector<Ingredients>& Recipe::getIngredients() const {
    return ingredients;
}