#include "json.hpp"
#include "mealPlanner.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

using json = nlohmann::json;
std::string plannerJson;
std::vector<Day> plannerVector;
RecipeObject hold = RecipeObject(0);

MealPlanner::MealPlanner()
{
    // std::cout << "Constructing meal planner..." << std::endl;
    Day monday =  Day(0);
    Day tuesday =  Day(1);
    Day wednesday =  Day(2);
    Day thursday =  Day(3);
    Day friday =  Day(4);
    Day saturday =  Day(5);
    Day sunday =  Day(6);
    initialiseDays(monday);
    initialiseDays(tuesday);
    initialiseDays(wednesday);
    initialiseDays(thursday);
    initialiseDays(friday);
    initialiseDays(saturday);
    initialiseDays(sunday);
    plannerVector.push_back(monday);
    plannerVector.push_back(tuesday);
    plannerVector.push_back(wednesday);
    plannerVector.push_back(thursday);
    plannerVector.push_back(friday);
    plannerVector.push_back(saturday);
    plannerVector.push_back(sunday);
    std::cout << plannerVector.size() << std::endl;
    std::cout << plannerVector[0].getLunch() << std::endl;
}

void MealPlanner::initialiseDays(Day day){
    day.setMeal(hold,0);
    day.setMeal(hold,1);
    day.setMeal(hold,2);
}

bool MealPlanner::addToPlanner(std::string recipeName, int recipeId, std::string day, std::string meal)
{
    std::cout << "Add to Planner called" << std::endl;

    int dayNum;
    int mealNum;
    std::string mealID;
    std::string mealName;
    std::string recipeID = std::to_string(recipeId);

    // RecipeDatabase recipeDB;
    // Recipe addRecipe = recipeDB.getRecipeById(recipeId);
    RecipeObject addRecipe = RecipeObject(recipeId);
    dayNum = getDayNum(day);
    std::cout << "recipeobject made" << std::endl;
    if (meal == "Breakfast")
    {
        mealNum=0;
        mealName = "breakfast";
        mealID = "breakfastID";
    }
    else if (meal == "Lunch")
    {
        mealNum=1;
        mealName = "lunch";
        mealID = "lunchID";
    }
    else if (meal == "Dinner")
    {
        mealNum=2;
        mealName = "dinner";
        mealID = "dinnerID";
    }
    else if (meal == "Snack")
    {
        mealNum=3;
        mealName = "snack";
        mealID = "snackID";
    }

    std::cout << plannerVector[0].getBreakfast() << std::endl;
try {
    plannerVector[dayNum].setMeal(addRecipe, mealNum);
  // Code that you want to try to execute
    std::cout << "plannervector found" << std::endl;
    std::cout << "day and num set " << dayNum << "    " << mealName << std::endl;
} catch (std::exception) {
    std::cout << "plannervector fail" << std::endl;
  // Code that you want to execute if an exception occurs
}
    // Day newMeal =  *addMeal;
    // newMeal.setMeal(*addRecipe, mealNum);
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

Day &MealPlanner::getDay(int dayNumber)
{
    if (dayNumber > 6 || dayNumber < 0)
    {
        std::cout << "Index out of range! Returning monday." << std::endl;
        return days[0];
    }
    else
    {
        return days[dayNumber];
    }
}

std::string MealPlanner::getPlannerJson() const
{
    std::cout << "Get Planner json called" << std::endl;
    return plannerJson;
}

// Day *MealPlanner::getDays()
// {
//     return days;
// }