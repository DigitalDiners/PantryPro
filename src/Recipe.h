#ifndef RECIPE_H
#define RECIPE_H

#include "Ingredients.h"
#include <string>
#include <vector>
using namespace std;

/** Recipe class
 * <p>
 * Get information of recipes etc
 * Set new information on recipes
 * Currently all recipes stored in textfile called DummyData
*/

class Recipe {
public:
    int recipeID;
    string recipeName;
    string prepTime;
    string totalTime;
    string category;
    float calories;

    /**
     * setting methods to change or create a recipe
     */
    void setRecipeID(int id);
    void setRecipeName(const string& name);
    void setPrepTime(const string& prep);
    void setTotalTime(const string& total);
    void setCategory(const string& cat);
    void setCalories(float cal);
    void addIngredient(const Ingredients& ingredient);


    /**
     * getting methods to get all parts of each recipe
     */
    int getRecipeID(Recipe);
    string getRecipeName(Recipe);
    string getPrepTime(Recipe);
    string getTotalTime(Recipe);
    string getCategory(Recipe);
    float getCalories(Recipe);
    const vector<Ingredients>& getIngredients() const;

private:
    vector<Ingredients> ingredients;
};

#endif
