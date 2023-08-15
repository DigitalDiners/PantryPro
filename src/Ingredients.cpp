#include "Ingredients.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>


using namespace std;

vector<string> ingredients;

Ingredients::Ingredients() {}

void Ingredients::getNames() const {
    if (ingredients.size()==0){
        cout << "There are no ingredients listed\n";
    }else{
        for(const string ingredient : ingredients){
            cout<<" Here is the list of ingredients you have\n";
            cout << "- "<<ingredient<<"\n";
        }
    }
}

void Ingredients::addIngredient(string newIngredient) {
    ingredients.push_back(newIngredient);
}

bool Ingredients::haveIngredient(string newIngredient) const{
    const char *newIn = newIngredient.c_str();
    for(const string ingredient : ingredients){
        const char *oldIn = ingredient.c_str();
        if(strcmp(newIn, oldIn)){
            return false;
        }
    }
    return true;
}