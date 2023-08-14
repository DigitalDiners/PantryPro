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
int Recipe::getRecipeID(int id) { 
    return recipeID; 
}
    
string Recipe::getRecipeName(const string& name) { 
    return recipeName; 
}
    
string Recipe::getPrepTime(const string& prep) { 
    return prepTime; 
}
    
string Recipe::getTotalTime(const string& total) { 
    return totalTime; 
}

string Recipe::getCategory(const string& cat) {
     return category; 
}

float Recipe::getCalories(float cal) { 
    return calories; 
}

const vector<Ingredients>& Recipe::getIngredients() const {
    return ingredients;
}