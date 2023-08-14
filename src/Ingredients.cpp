#include "Ingredients.h"
using namespace std;


Ingredients::Ingredients(const string& name) : name(name) {}

string Ingredients::getName() const {
    return name;
}

void Ingredients::addIngredient() const {}
