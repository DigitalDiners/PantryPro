#include "ingredient.h"

Ingredient::Ingredient(int ingredientId, const std::string &ingredientName):
    ingredientId(ingredientId), ingredientName(ingredientName) {}

int Ingredient::getIngredientId() const {
    return ingredientId;
}

std::string Ingredient::getIngredientName() const {
    return ingredientName;
}