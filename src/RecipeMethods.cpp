#include "RecipeMethods.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> 
#include <unistd.h>
#include <vector>
#include <sstream>


/**
 * ChatGPT help
*/

/**
 * Method to filter the recipes by available ingredients
 * <p>
 * @input recipe vector
 * @input ingredient vector
 * @output filtered recipe vector
*/
std::vector<Recipe> filterRecipesByIngredients(const std::vector<Recipe>& allRecipes, const std::vector<Ingredients>& ingredients) {
   std::vector<Recipe> filteredRecipes;

    for (const Recipe& recipe : allRecipes) {
        bool includesAllIngredients = true;

        for (const Ingredients& ingredient : ingredients) {
            bool ingredientFound = true;

            for (const Ingredients& recipeIngredient : recipe.getIngredients()) {
                if (!(recipeIngredient.getNames() == ingredient.getNames())) {
                    ingredientFound = false;
                    break;
                }
            }

            if (!ingredientFound) {
                includesAllIngredients = false;
                break;
            }
        }

        if (includesAllIngredients) {
            filteredRecipes.push_back(recipe);
        }
    }

    return filteredRecipes;
    }


/**
 * Method to add a new recipe
 * @input curr recipe vector
 * @input new recipe
 * @input DummyData file
*/

void addRecipe(std::vector<Recipe>& recipes, const Recipe& newRecipe, const std::string& filename) {
    recipes.push_back(newRecipe);

    std::ofstream outputFile(filename, std::ios::app); // Append mode

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    outputFile << newRecipe.recipeID << ","
               << newRecipe.recipeName << ","
               << newRecipe.prepTime << ","
               << newRecipe.totalTime << ","
               << newRecipe.category << ","
               << newRecipe.calories << "\n";

    outputFile.close();
}


/**
 * Method to edit a recipe - unsure if we want this but the code inside could be useful
*/
vector<Recipe> editRecipe(std::vector<Recipe>& recipes, const Recipe& oldRecipe, const Recipe& changedRecipe, const std::string& filename){
    
    auto it = find(recipes.begin(), recipes.end(), oldRecipe);

    if(it!=recipes.end()){//old recipe found in vector
        int index = it-recipes.begin();
        replace(recipes.begin(), recipes.end(), oldRecipe, changedRecipe);//replace the old with new recipe
        cout<<"Recipe has been changed";

    }else{//Old recipe not found in the vector
        cout<<"Original recipe could not be found";
    }
    return recipes;
}

