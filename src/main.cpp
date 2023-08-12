#include "MyApp.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> 
#include <unistd.h>
#include <vector>
#include <sstream>

char *getcwd(char *buf, size_t size);
using namespace std;

/** Recipe class
 * <p>
 * Get information of recipes etc
 * Set new information on recipes
 * Currently all recipes stored in textfile called DummyData
*/
class Recipe{

  /**
   * Constructor of sorts?
  */
  public:
    int recipeID;
    string recipeName;
    string prepTime;
    string totalTime;
    string category;
    float calories;

    /**
     * setting methods to create or edit recipes
    */
    void setRecipeID(int id) { recipeID = id; }
    void setRecipeName(const string& name) { recipeName = name; }
    void setPrepTime(const string& prep) { prepTime = prep; }
    void setTotalTime(const string& total) { totalTime = total; }
    void setCategory(const string& cat) { category = cat; }
    void setCalories(float cal) { calories = cal; }
 
    /**
     * getting methods to get all parts of each recipe
     */
    int getRecipeID(int id) { return recipeID; }
    string getRecipeName(const string& name) { return recipeName; }
    string getPrepTime(const string& prep) { return prepTime; }
    string getTotalTime(const string& total) { return totalTime; }
    string getCategory(const string& cat) { return category; }
    float getCalories(float cal) { return calories; }
};

/**
 * Method to add a new recipe
*/
void addNewRecipe(vector<Recipe>& recipes, const Recipe& newRecipe, const string& filename) {
    recipes.push_back(newRecipe);

    ofstream outputFile(filename, ios::app); // Append mode

    if (!outputFile.is_open()) {
        cerr << "Error opening file for writing!" << endl;
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


int main()
{
  vector<Recipe> recipes;  // Vector to store recipes
  ifstream inputFile("src/DummyData.txt");  // Change "recipes.txt" to your file's name

if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        Recipe recipe;
        string temp;

        // Read and parse the comma-separated values
        if (getline(iss, temp, ','))
            recipe.recipeID = stoi(temp);
        if (getline(iss, recipe.recipeName, ','))
            ;
        if (getline(iss, recipe.prepTime, ','))
            ;
        if (getline(iss, recipe.totalTime, ','))
            ;
        if (getline(iss, recipe.category, ','))
            ;
        if (getline(iss, temp, ','))
            recipe.calories = stof(temp);

        recipes.push_back(recipe);
    }

    inputFile.close();

    // Now the 'recipes' vector contains the parsed data
    // You can iterate over it and access the Recipe objects
    cout << "\nUpdated list of recipes:\n";
    for (const Recipe& recipe : recipes) {
        cout << "Recipe ID: " << recipe.recipeID << "\n"
                  << "Name: " << recipe.recipeName << "\n"
                  << "Prep Time: " << recipe.prepTime << "\n"
                  << "Total Time: " << recipe.totalTime << "\n"
                  << "Category: " << recipe.category << "\n"
                  << "Calories: " << recipe.calories << "\n"
                  << endl;
    }
  
  return 0;
}
