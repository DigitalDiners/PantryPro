#include "recipe.h"


Recipe::Recipe(int id, const std::string & name, int aId, const std::string & aName, int cTime, int pTime, int tTime, const std::string & dPublished, const std::string & desc, const std::string & cat, int cal, int serv, int yieldQ)
{
}

int Recipe::getId() const {
    return recipeId;
}

std::string Recipe::getName() const {
    return recipeName;
}

int Recipe::getAuthorId() const {
    return authorId;
}

int Recipe::getCookTime() const {
    return cookTime;
}

int Recipe::getPrepTime() const {
    return prepTime;
}

int Recipe::getTotalTime() const {
    return totalTime;
}

std::string Recipe::getDatePublished() const {
    return datePublished;
}

std::string Recipe::getDescription() const {
    return description;
}

std::string Recipe::getCategory() const {
    return category;
}

int Recipe::getCalories() const {
    return calories;
}

int Recipe::getServings() const {
    return servings;
}

int Recipe::getYieldQuantity() const {
    return yieldQuantity;
}
