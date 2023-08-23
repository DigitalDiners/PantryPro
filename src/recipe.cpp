#include "recipe.h"

// recipe::recipe(int id, const std::string& name, int aId,
//                int cTime, int pTime, int tTime, const std::string& dPublished,
//                const std::string& desc, const std::string& cat,
//                int cal, int serv, int yieldQ) 
//     : recipeId(id), recipeName(name), authorId(aId),
//       cookTime(cTime), prepTime(pTime), totalTime(tTime), datePublished(dPublished),
//       description(desc), category(cat), calories(cal), servings(serv), yieldQuantity(yieldQ) {}

recipe::recipe(int id, const std::string & name, int aId, const std::string & aName, int cTime, int pTime, int tTime, const std::string & dPublished, const std::string & desc, const std::string & cat, int cal, int serv, int yieldQ)
{
}

int recipe::getId() const {
    return recipeId;
}

std::string recipe::getName() const {
    return recipeName;
}

int recipe::getAuthorId() const {
    return authorId;
}

int recipe::getCookTime() const {
    return cookTime;
}

int recipe::getPrepTime() const {
    return prepTime;
}

int recipe::getTotalTime() const {
    return totalTime;
}

std::string recipe::getDatePublished() const {
    return datePublished;
}

std::string recipe::getDescription() const {
    return description;
}

std::string recipe::getCategory() const {
    return category;
}

int recipe::getCalories() const {
    return calories;
}

int recipe::getServings() const {
    return servings;
}

int recipe::getYieldQuantity() const {
    return yieldQuantity;
}
