/**
 * @file recipeObject.cpp
 * @author Luke Webb
 * @brief Class abstraction for recipe objects, used for weekly meal planner and days
 * @version 0.1
 * @date 2023-08-18
 * 
 */
#include "recipeObject.h"
#include <string>


RecipeObject::RecipeObject(int recipeID){
    this->recipeID = recipeID;
}
  
int RecipeObject::getRecipeID() const{
    return recipeID;
}

void RecipeObject::setName(const std::string &name){
    this->name = name;
}
    
std::string RecipeObject::getName() const{
    return name;
}

void RecipeObject::setPrepTime(const std::string &prepTime){
    this->prepTime = prepTime;
}
   
std::string RecipeObject::getPrepTime() const{
    return prepTime;
}
    
void RecipeObject::setTotalTime(const std::string &totalTime){
    this->totalTime = totalTime;
}
    
std::string RecipeObject::getTotalTime() const{
    return totalTime;
}

    
void RecipeObject::setCategory(const std::string &category){
    this->category = category;
}

std::string RecipeObject::getCategory() const{
    return category;
}

    
void RecipeObject::setCalories(float calories){
    this->calories = calories;
}
    
float RecipeObject::getCalories() const{
    return calories;
}
