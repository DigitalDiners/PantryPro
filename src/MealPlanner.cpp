#include "mealPlanner.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "recipe.h"

RecipeObject hold = RecipeObject(0);
std::vector<std::vector<int> > recipeVector;

MealPlanner::MealPlanner()
{
    // std::vector<Recipe> monday(4);
    // std::vector<Recipe> tuesday(4);
    // std::vector<Recipe> wednesday(4);
    // std::vector<Recipe> thursday(4);
    // std::vector<Recipe> friday(4);
    // std::vector<Recipe> saturday(4);
    // std::vector<Recipe> sunday(4);
    // std::vector<std::vector<Recipe> > recipeVector = {monday, tuesday, wednesday, thursday, friday, saturday, sunday};
    std::vector<std::vector<int> > recipeVector(7, std::vector<int>(3));
    std::cout << recipeVector.size() << std::endl;
    std::cout << recipeVector.size() << std::endl;
}


bool MealPlanner::addToPlanner(std::string recipeName, int recipeId, std::string day, std::string meal)
{
    std::cout << "Add to Planner called" << std::endl;

    int dayNum;
    int mealNum;
    // std::string recipeID = std::to_string(recipeId);
    // RecipeDatabase recipeDB;
    // Recipe addRecipe = recipeDB.getRecipeById(recipeId);
    dayNum = getDayNum(day);
    std::cout << "recipe made" << std::endl;
    if (meal == "Breakfast")
    {
        mealNum=0;
    }
    else if (meal == "Lunch")
    {
        mealNum=1;
    }
    else if (meal == "Dinner")
    {
        mealNum=2;
    }
    else if (meal == "Snack")
    {
        mealNum=3;
    }
    recipeVector[dayNum][mealNum] = recipeId;

    return true;

}

int MealPlanner::getDayNum(std::string day){
    int dayNum;
        if (day == "Monday")
    {
        dayNum = 0;
    }
    else if (day == "Tuesday")
    {
        dayNum = 1;
    }
    else if (day == "Wednesday")
    {
        dayNum = 2;
    }
    else if (day == "Thursday")
    {
        dayNum = 3;
    }
    else if (day == "Friday")
    {
        dayNum = 4;
    }
    else if (day == "Saturday")
    {
        dayNum = 5;
    }
    else if (day == "Sunday")
    {
        dayNum = 6;
    }
    return dayNum;
}

MealPlanner::~MealPlanner()
{
    delete[] days; // Clean up the dynamically allocated memory
}


std::string MealPlanner::getPlannerJson() const
{
    std::string plannerJson;
    
    std::cout << "Get Planner json called" << std::endl;
    return plannerJson;
}

// Day *MealPlanner::getDays()
// {
//     return days;
// }