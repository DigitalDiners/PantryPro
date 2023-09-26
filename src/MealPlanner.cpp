#include "json.hpp"
#include "mealPlanner.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

using json = nlohmann::json;
std::string plannerJson;

MealPlanner::MealPlanner()
{
    // std::cout << "Constructing meal planner..." << std::endl;

    try{
        // std::ifstream jsonFile("./assets/data/planner.json");
        std::ifstream jsonFile("../Resources/assets/data/planner.json");
        if (!jsonFile.is_open()) {
            std::cerr << "Error opening JSON file!" << std::endl;
            throw 404;
        }
        std::ostringstream tmp;
        tmp<<jsonFile.rdbuf();
        plannerJson = tmp.str();

        // Close the file to release resources.
        jsonFile.close();
    }catch(const std::exception& e) {
        // Handle the exception here
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

}

bool MealPlanner::addToPlanner(std::string recipeName, int recipeId, std::string day, std::string meal)
{
    json data;
    std::cout << "Add to Planner called" << std::endl;
    // Populate the JSON object with data
    data["recipeName"] = recipeName;
    data["recipeId"] = recipeId;
    int dayNum;
    std::string mealNum;
    // std::ifstream ifs("./assets/data/planner.json");
    std::ifstream ifs("../Resources/assets/data/planner.json");
    json readIn;
    ifs >> readIn;
    std::cout << "ifstream" << std::endl;
    //switch case for monday through to sunday, 0 through to 6
    if(day=="Monday"){
        dayNum = 0;
    }else if(day=="Tuesday"){
        dayNum = 1;
    }else if(day=="Wednesday"){
        dayNum = 2;
    }else if(day=="Thursday"){
        dayNum = 3;
    }else if(day=="Friday"){
        dayNum = 4;
    }else if(day=="Saturday"){
        dayNum = 5;
    }else if(day=="Sunday"){
        dayNum = 6;
    }
    if(meal=="Breakfast"){
        mealNum = "breakfast";
    }else if(meal=="Lunch"){
        mealNum = "lunch";
    }else if(meal=="Dinner"){
        mealNum = "dinner";
    }else if(meal=="Snack"){
        mealNum = "snack";
    }
    // Check if the value is None.
        std::cout << "day and num set"<<dayNum<<"    "<<mealNum << std::endl;

    if (readIn[dayNum][mealNum].is_null())
    {

        // The block is not filled.
        std::cout << "The block is not filled." << std::endl;
        // data["day"] = day;
        // data["meal"] = meal;

        // Specify the file name to write to
        // std::string filename = "./assets/data/planner.json";
        std::string filename = "../Resources/assets/data/planner.json";

        // Open a file stream for writing
        std::ofstream file(filename);

        if (file.is_open())
        {
            // Write the JSON data to the file
            // specify where in file to place data
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
    std::cout << "Get Planner json called" << std::endl;
    return plannerJson;
}

Day *MealPlanner::getDays()
{
    return days;
}