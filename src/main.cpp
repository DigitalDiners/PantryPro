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
#include "Recipe.h"
#include "Ingredients.h"


using namespace std;

vector<Recipe> populate(){
  vector<Recipe> recipes;  // Vector to store recipes
      ifstream inputFile("src/DummyData.txt");  
  if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return recipes;
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
    return recipes;

}


int main()
{
  vector<Recipe> recipes;  // Vector to store recipes

  //part of dummydata - change for sql when ready. add code to parse SQL into vector? or just store all recipeID.


    recipes = populate();
    if(recipes.size()==0){
        cout<<"no recipes loaded!"<< endl;
        return 1;
    }

    int option;
    cout << "Would you like to: \n[1] View the List of recipes? \n[2] Add an ingredient? \n[3] Add a recipe?\n";
    cin >> option;
    cout<< "Your option is "<< option;

    // Now the 'recipes' vector contains the parsed data
    // You can iterate over it and access the Recipe objects
    if(option == 1){
            cout << "\nList of recipes:\n";
        for (const Recipe& recipe : recipes) {
        cout << "Recipe ID: " << recipe.recipeID << "\n"
                  << "Name: " << recipe.recipeName << "\n"
                  << "Prep Time: " << recipe.prepTime << "\n"
                  << "Total Time: " << recipe.totalTime << "\n"
                  << "Category: " << recipe.category << "\n"
                  << "Calories: " << recipe.calories << "\n"
                  << endl;
        }
    }

    if(option == 2){

    }
    if(option == 3){

    }
  
  return 0;
}
