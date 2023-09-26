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
void MealPlanner::findPath(){
    json source = R"(
        [ 
    {
        "day":"Monday",
        "breakfast":"",
        "breakfastID": "",
        "lunch":"",
        "lunchID":"",
        "dinner":"",
        "dinnerID":"",
        "snack":"",
        "snackID":""
    },
    {
        "day":"Tuesday",
        "breakfast":"",
        "breakfastID": "",
        "lunch":"",
        "lunchID":"",
        "dinner":"",
        "dinnerID":"",
        "snack":"",
        "snackID":""
    },
    {
        "day":"Wednesday",
        "breakfast":"",
        "breakfastID": "",
        "lunch":"",
        "lunchID":"",
        "dinner":"",
        "dinnerID":"",
        "snack":"",
        "snackID":""
    }
    ]
    )"_json;

    json target = R"(
        [ 
    {
        "day":"Monday",
        "breakfast":"potato",
        "breakfastID": "123",
        "lunch":"ffff",
        "lunchID":"543345",
        "dinner":"",
        "dinnerID":"",
        "snack":"",
        "snackID":""
    },
    {
        "day":"Tuesday",
        "breakfast":"",
        "breakfastID": "",
        "lunch":"",
        "lunchID":"",
        "dinner":"summer",
        "dinnerID":"432",
        "snack":"",
        "snackID":""
    },
    {
        "day":"Wednesday",
        "breakfast":"cdcds",
        "breakfastID": "3242",
        "lunch":"",
        "lunchID":"",
        "dinner":"",
        "dinnerID":"",
        "snack":"",
        "snackID":""
    }
    ]
    )"_json;
       // create the patch
    json patch = json::diff(source, target);

    // roundtrip
    json patched_source = source.patch(patch);

    // output patch and roundtrip result
    std::cout << std::setw(4) << patch << "\n\n"
              << std::setw(4) << patched_source << std::endl;
}
void MealPlanner::reopenFile(){
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

    int dayNum;
    std::string mealName;

    //windows
    // std::ifstream ifs("./assets/data/planner.json");
    //macOS
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
    data["day"] = day;

    if(meal=="Breakfast"){
        mealName = "breakfast";
        data["breakfast"] = recipeName;
        data["breakfastID"] = recipeId;
    }else if(meal=="Lunch"){
        mealName = "lunch";
        data["lunch"] = recipeName;
        data["lunchID"] = recipeId;
    }else if(meal=="Dinner"){
        mealName = "dinner";
        data["dinner"] = recipeName;
        data["dinnerID"] = recipeId;
    }else if(meal=="Snack"){
        mealName = "snack";
        data["snack"] = recipeName;
        data["snackID"] = recipeId;
    }
        std::cout << "day and num set"<<dayNum<<"    "<<mealName << std::endl;


        // Specify the file name to write to
        // std::string filename = "./assets/data/planner.json";
        std::string filename = "../Resources/assets/data/planner.json";

        // Open a file stream for writing
        std::ofstream file(filename);

        if (file.is_open())
        {
            json patch = R"(
                [
                    { "op": "replace", 
                    "path": "/dayNum/meal",
                    "value": "recipeName"},
                    { "op": "replace",
                    "path": "/dayNum/mealID",
                    "value": "recipeID"}
                ]
            )"_json;
            // Write the JSON data to the file
            // specify where in file to place data
            // file << data.dump(4); // The argument specifies the indentation level
            readIn.patch(patch);
            file<<readIn.dump();
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