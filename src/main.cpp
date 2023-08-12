#include "MyApp.h"
#include "Recipe.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> 
#include <unistd.h>
#include <vector>
#include <sstream>

using namespace std;


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



  //part of dummydata - change for sql when ready. add code to parse SQL into vector? or just store all recipeID.

  ifstream inputFile("src/DummyData.txt");  
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
