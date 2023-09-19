#include "json.hpp"
#include "mealPlanner.h"
#include <fstream>
#include <iostream>
#include <sstream>

using json = nlohmann::json;

MealPlanner::MealPlanner()
{
    std::cout << "Constructing meal planner..." << std::endl;

    std::ifstream jsonFile("../assets/data/planner.json");
    std::ostringstream tmp;
    tmp << jsonFile.rdbuf();
    plannerJson = tmp.str();

    // std::ifstream planner_file("../assets/data/planner.json");
    // json planner = json::parse(planner_file);

    Day theDays[] = {Day(0), Day(1), Day(2), Day(3), Day(4), Day(5), Day(6)};

    days = theDays;

    // for(int dayIndex = 0; dayIndex < 7; dayIndex++){
    //     Day currentDay(dayIndex);

    //     RecipeObject breakfast(0);
    //     RecipeObject lunch(1);
    //     RecipeObject dinner(2);

    //     breakfast.setName(planner[dayIndex]["breakfast"]);
    //     breakfast.setName(planner[dayIndex]["lunch"]);
    //     breakfast.setName(planner[dayIndex]["dinner"]);

    //     currentDay.setMeal(breakfast, 0);
    //     currentDay.setMeal(lunch, 1);
    //     currentDay.setMeal(dinner, 2);

    //     days.push_back(currentDay);
    // }
}

bool MealPlanner::addToPlanner(std::string recipeName, int recipeId, std::string day, std::string meal)
{
    json data;

    // Populate the JSON object with data
    data["recipeName"] = recipeName;
    data["recipeId"] = recipeId;

    std::ifstream ifs("../assets/data/planner.json");
    json readIn;
    ifs >> readIn;

    // Check if the value is None.
    if (readIn[day][meal].is_null())
    {

        // The block is not filled.
        std::cout << "The block is not filled." << std::endl;
        // data["day"] = day;
        // data["meal"] = meal;
    
        // Specify the file name to write to
        std::string filename = "../assets/data/planner.json";

        // Open a file stream for writing
        std::ofstream file(filename);

        if (file.is_open())
        {
            // Write the JSON data to the file
            //specify where in file to place data
            file << data.dump(4); // The argument specifies the indentation level
            file.close();
            std::cout << "JSON data written to " << filename << std::endl;
            return true;
        }
        else
        {
            std::cerr << "Unable to open " << filename << " for writing." << std::endl;
            return false;
        }
    }
    else
    {

        // The block is already filled.
        std::cout << "The block is already filled." << std::endl;
        return false;
    }
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
    return plannerJson;
}

Day *MealPlanner::getDays()
{
    return days;
}