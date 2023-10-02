#include "json.hpp"
#include "mealPlanner.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

using json = nlohmann::json;
std::string plannerJson;
std::vector<Day*> mealPlanner;

MealPlanner::MealPlanner()
{
    // std::cout << "Constructing meal planner..." << std::endl;
    Day* monday = new Day(0);
    Day* tuesday = new Day(1);
    Day* wednesday = new Day(2);
    Day* thursday = new Day(3);
    Day* friday = new Day(4);
    Day* saturday = new Day(5);
    Day* sunday = new Day(6);
    mealPlanner.push_back(monday);
    mealPlanner.push_back(tuesday);
    mealPlanner.push_back(wednesday);
    mealPlanner.push_back(thursday);
    mealPlanner.push_back(friday);
    mealPlanner.push_back(saturday);
    mealPlanner.push_back(sunday);
}

bool MealPlanner::addToPlanner(std::string recipeName, int recipeId, std::string day, std::string meal)
{
    std::cout << "Add to Planner called" << std::endl;

    int dayNum;
    int mealNum;
    std::string mealID;
    std::string mealName;
    std::string recipeID = std::to_string(recipeId);

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
    std::cout << "day and num set " << dayNum << "    " << mealName << std::endl;

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