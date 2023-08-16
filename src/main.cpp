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
#include "Ingredients.h"
#include "Ingredients.cpp"
#include <stdbool.h>


using namespace std;

vector<Recipe> recipes;  // Vector to store recipes
Ingredients ingredientList;

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

vector<Recipe> options(int option, vector<Recipe> recipes){
    if(option == 0) {//view ingredients
        ingredientList.getNames();
    }else if(option == 1){// view recipes
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
    }else if(option == 2){// add ingredient
        string newIngredient;
        cout<< "Please enter the name of your ingredient to add\n";
        cin>>newIngredient;
        cout<<newIngredient;
        if(!ingredientList.haveIngredient(newIngredient)){
            ingredientList.addIngredient(newIngredient);
            cout<<"The ingredient has been added\n";
        }else{
            cout<<"That ingredient was already added\n";
        }

    }else if(option == 3){ // add recipe
        Recipe newrecipe;
        cout<<"Please enter\n Name:\n";
        cin>>newrecipe.recipeName;
        cout<<"Prep Time:\n";
        cin>>newrecipe.prepTime;
        cout<<"Total time:\n";
        cin>>newrecipe.totalTime;
        cout<<"Category:\n";
        cin>>newrecipe.category;
        cout<<"Calories:\n";
        cin>>newrecipe.calories;
        int finalIndex = recipes.size();
        //cout<<finalIndex<<'\n';
        newrecipe.recipeID = recipes[finalIndex-1].recipeID+1;
        //cout<<newrecipe.recipeID<<'\n';
        recipes.push_back(newrecipe);
    }else if(option == 4){// remove ingredient
        string removeThis;
        cout<< "Enter the name of the ingredient you want to remove\n";
        cin>> removeThis;
        ingredientList.removeIngredient(removeThis);
    }else if(option == 5){
    }else{
        cout<<"That is not a valid option\n";
    }
  return recipes;
}

int main()
{
    recipes = populate();
    if(recipes.size()==0){
        cout<<"no recipes loaded!"<< endl;
        return 1;
    }

    MyApp app;
    app.Run();

  //part of dummydata - change for sql when ready. add code to parse SQL into vector? or just store all recipeID in vector then get from recipeID

    int option;
    while(option!=5){
    cout << "Would you like to: \n[0] View the list of ingredients? \n[1] View the list of recipes? \n[2] Add an ingredient? \n[3] Add a recipe?\n[4] Remove an ingredient \n[5] Exit program\n";
    cin>>option;
    cout<< "Your option is "<< option<<"\n";
    recipes = options(option, recipes);
    }

    // Now the 'recipes' vector contains the parsed data
    // You can iterate over it and access the Recipe objects
  return 0;
}
