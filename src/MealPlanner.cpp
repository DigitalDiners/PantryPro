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
    reopenFile();
    // findPath();
}
void MealPlanner::reopenFile()
{
    try
    {
// std::ifstream jsonFile("./assets/data/planner.json");
#if _WIN32
        std::ifstream jsonFile("./assets/data/planner.json");
#elif __APPLE__
        std::ifstream jsonFile("../Resources/assets/data/planner.json");
#endif
        if (!jsonFile.is_open())
        {
            std::cerr << "Error opening JSON file!" << std::endl;
            throw 404;
        }
        std::ostringstream tmp;
        tmp << jsonFile.rdbuf();
        plannerJson = tmp.str();

        // Close the file to release resources.
        jsonFile.close();
    }
    catch (const std::exception &e)
    {
        // Handle the exception here
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

bool MealPlanner::addToPlanner(std::string recipeName, int recipeId, std::string day, std::string meal)
{
    json data;
    std::cout << "Add to Planner called" << std::endl;
    json readIn;

    int dayNum;
    std::string mealID;
    std::string mealName;
    std::string recipeID = std::to_string(recipeId);

#if _WIN32
    std::string filename = "./assets/data/planner.json";
#elif __APPLE__
    std::string filename = "../Resources/assets/data/planner.json";
#endif
    try
    {

        std::cout << "readIn" << std::endl;
        std::ifstream ifs(filename);
        std::cout << "ifs opened" << std::endl;
        if (!ifs.is_open())
        {
            std::cerr << "Error opening JSON file!" << std::endl;
            throw 404;
        }
        ifs>>readIn;
        std::cout << "ifstream into readin" << std::endl;

        // Close the file to release resources.
        ifs.close();
    }
    catch (const std::exception &e)
    {
        // Handle the exception here
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

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
    data["day"] = day;

    if (meal == "Breakfast")
    {
        mealName = "breakfast";
        mealID = "breakfastID";
    }
    else if (meal == "Lunch")
    {
        mealName = "lunch";
        mealID = "lunchID";
    }
    else if (meal == "Dinner")
    {
        mealName = "dinner";
        mealID = "dinnerID";
    }
    else if (meal == "Snack")
    {
        mealName = "snack";
        mealID = "snackID";
    }
    std::cout << "day and num set " << dayNum << "    " << mealName << std::endl;

    // Open a file stream for writing
    std::ofstream file(filename);
    std::string daynumber = std::to_string(dayNum);

    if (file.is_open())
    {
        std::string patch = "[{ 'op': 'replace', 'path': '/" + daynumber + "/" + meal + "', 'value': '" + recipeName + "'},{ 'op': 'replace','path': '/" + daynumber + "/" + mealID + "','value': '" + recipeID + "'}]";

        
        std::cout << patch << std::endl;

        json patchThis = json::parse(patch);
        std::cout << "parse the patch" << dayNum << "    " << mealName << std::endl;
        // Write the JSON data to the file
        // specify where in file to place data
        // file << data.dump(4); // The argument specifies the indentation level
        readIn.patch_inplace(patchThis);
        std::cout << "patch into readin" << dayNum << "    " << mealName << std::endl;
        readIn.emplace();
        std::cout << "emplaced" << dayNum << "    " << mealName << std::endl;
        file << readIn.dump();
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