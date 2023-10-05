#include "mealPlanner.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "recipe.h"
#include "json.hpp"

using json = nlohmann::json;

MealPlanner::MealPlanner()
:recipeVector(7, std::vector<int>(3))
{   
    // for(std::vector<int> days:recipeVector){
    //     for(int meals:days){
    //         meals = 0;
    //     }
    // }

    try{
        // std::ifstream jsonFile("./assets/data/planner.json");
        #if _WIN32
            std::ifstream jsonFile("./assets/data/planner.json");
        #elif __APPLE__
            std::ifstream jsonFile("../Resources/assets/data/planner.json");
        #endif
        if (!jsonFile.is_open())
        {
            std::cerr << "Error opening JSON file!" << std::endl;
        }
        std::ostringstream tmp;
        tmp<< jsonFile.rdbuf();
        plannerJsonString = tmp.str();

        jsonFile.close();
    }catch(const std::exception& e) {
        std::cerr << "Unable to open file: planner.json" << std::endl;
    }

    json plannerJson = json::parse(plannerJsonString);

    for(int day = 0; day < recipeVector.size(); day++){
        recipeVector[day][0] = std::stoi(plannerJson[day]["breakfastID"].get<std::string>());
        recipeVector[day][1] = std::stoi(plannerJson[day]["lunchID"].get<std::string>());
        recipeVector[day][2] = std::stoi(plannerJson[day]["dinnerID"].get<std::string>());
    }

    std::cout << "Planner string saved to vector" << std::endl;
    
    plannerJsonString.clear();

    plannerJsonString +="[{\"name\":\"Monday\", \"breakfast\":\""+name(recipeVector[0][0])+"\", \"lunch\": \""+name(recipeVector[0][1])+"\", \"dinner\": \""+name(recipeVector[0][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Tuesday\", \"breakfast\":\""+name(recipeVector[1][0])+"\", \"lunch\": \""+name(recipeVector[1][1])+"\", \"dinner\": \""+name(recipeVector[1][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Wednesday\", \"breakfast\":\""+name(recipeVector[2][0])+"\", \"lunch\": \""+name(recipeVector[2][1])+"\", \"dinner\": \""+name(recipeVector[2][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Thursday\", \"breakfast\":\""+name(recipeVector[3][0])+"\", \"lunch\": \""+name(recipeVector[3][1])+"\", \"dinner\": \""+name(recipeVector[3][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Friday\", \"breakfast\":\""+name(recipeVector[4][0])+"\", \"lunch\": \""+name(recipeVector[4][1])+"\", \"dinner\": \""+name(recipeVector[4][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Saturday\", \"breakfast\":\""+name(recipeVector[5][0])+"\", \"lunch\": \""+name(recipeVector[5][1])+"\", \"dinner\": \""+name(recipeVector[5][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Sunday\", \"breakfast\":\""+name(recipeVector[6][0])+"\", \"lunch\": \""+name(recipeVector[6][1])+"\", \"dinner\": \""+name(recipeVector[6][2])+"\"}";
    plannerJsonString += "]";
    
    std::cout << "Planner string set" << std::endl;
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
    // std::cout << "recipe made" << std::endl;
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
    // std::cout << recipeId << std::endl;

    // std::cout << recipeVector[dayNum][mealNum] << std::endl;
    plannerJsonString.clear();

    std::cout << "planner string made" << std::endl;
    plannerJsonString +="[{\"name\":\"Monday\", \"breakfast\":\""+name(recipeVector[0][0])+"\", \"lunch\": \""+name(recipeVector[0][1])+"\", \"dinner\": \""+name(recipeVector[0][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Tuesday\", \"breakfast\":\""+name(recipeVector[1][0])+"\", \"lunch\": \""+name(recipeVector[1][1])+"\", \"dinner\": \""+name(recipeVector[1][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Wednesday\", \"breakfast\":\""+name(recipeVector[2][0])+"\", \"lunch\": \""+name(recipeVector[2][1])+"\", \"dinner\": \""+name(recipeVector[2][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Thursday\", \"breakfast\":\""+name(recipeVector[3][0])+"\", \"lunch\": \""+name(recipeVector[3][1])+"\", \"dinner\": \""+name(recipeVector[3][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Friday\", \"breakfast\":\""+name(recipeVector[4][0])+"\", \"lunch\": \""+name(recipeVector[4][1])+"\", \"dinner\": \""+name(recipeVector[4][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Saturday\", \"breakfast\":\""+name(recipeVector[5][0])+"\", \"lunch\": \""+name(recipeVector[5][1])+"\", \"dinner\": \""+name(recipeVector[5][2])+"\"}";
    plannerJsonString +=",{\"name\":\"Sunday\", \"breakfast\":\""+name(recipeVector[6][0])+"\", \"lunch\": \""+name(recipeVector[6][1])+"\", \"dinner\": \""+name(recipeVector[6][2])+"\"}";
    plannerJsonString += "]";

    std::cout << plannerJsonString << std::endl;
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

std::string MealPlanner::getDayName(int dayNumber) {
    const std::string daysOfWeek[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
    };

    // Check if the input is within a valid range
    if (dayNumber >= 0 && dayNumber < 7) {
        return daysOfWeek[dayNumber];
    } else {
        return "Invalid day number";
    }
}

MealPlanner::~MealPlanner()
{
    delete[] days; // Clean up the dynamically allocated memory
    
}

std::string MealPlanner::name(int recipeId) const{
    std::cout << "getName called" << std::endl;
    if(recipeId==0){
        return "Undecided";
    }
    RecipeDatabase recipeDB;
    Recipe recipe = recipeDB.getRecipeById(recipeId);
    std::cout<<recipe.getName()<<std::endl;
    return recipe.getName();
}

std::string MealPlanner::getPlannerJson() const
{
    std::cout << "Get Planner json called" << std::endl;
    return plannerJsonString;
}

void MealPlanner::Save()
{
    std::cout << "Save called" << std::endl;
    std::string plannerJsonString;
    
    plannerJsonString +="[{\"name\":\"Monday\", \"breakfastID\" : \"" + std::to_string(recipeVector[0][0]) + "\" , \"lunchID\" : \"" + std::to_string(recipeVector[0][1]) + "\" , \"dinnerID\" : \"" + std::to_string(recipeVector[0][2]) + "\" }";
    plannerJsonString +=",{\"name\":\"Tuesday\", \"breakfastID\" : \"" + std::to_string(recipeVector[1][0]) + "\" , \"lunchID\" : \"" + std::to_string(recipeVector[1][1]) + "\" , \"dinnerID\" : \"" + std::to_string(recipeVector[1][2]) + "\" }";
    plannerJsonString +=",{\"name\":\"Wednesday\", \"breakfastID\" : \"" + std::to_string(recipeVector[2][0]) + "\" , \"lunchID\" : \"" + std::to_string(recipeVector[2][1]) + "\" , \"dinnerID\" : \"" + std::to_string(recipeVector[2][2]) + "\" }";
    plannerJsonString +=",{\"name\":\"Thursday\", \"breakfastID\" : \"" + std::to_string(recipeVector[3][0]) + "\" , \"lunchID\" : \"" + std::to_string(recipeVector[3][1]) + "\" , \"dinnerID\" : \"" + std::to_string(recipeVector[3][2]) + "\" }";
    plannerJsonString +=",{\"name\":\"Friday\", \"breakfastID\" : \"" + std::to_string(recipeVector[4][0]) + "\" , \"lunchID\" : \"" + std::to_string(recipeVector[4][1]) + "\" , \"dinnerID\" : \"" + std::to_string(recipeVector[4][2]) + "\" }";
    plannerJsonString +=",{\"name\":\"Saturday\", \"breakfastID\" : \"" + std::to_string(recipeVector[5][0]) + "\" , \"lunchID\" : \"" + std::to_string(recipeVector[5][1]) + "\" , \"dinnerID\" : \"" + std::to_string(recipeVector[5][2]) + "\" }";
    plannerJsonString +=",{\"name\":\"Sunday\", \"breakfastID\" : \"" + std::to_string(recipeVector[6][0]) + "\" , \"lunchID\" : \"" + std::to_string(recipeVector[6][1]) + "\" , \"dinnerID\" : \"" + std::to_string(recipeVector[6][2]) + "\" }";
    plannerJsonString += "]";

    std::cout << "Planner string made" << std::endl;
    
    try {
        #if __APPLE__
            std::ofstream outFile("../Resources/assets/data/planner.json");
        #elif _WIN32
            std::ofstream outFile("./assets/data/planner.json");
        #endif

        if (outFile.is_open()) {
            outFile << plannerJsonString;
            outFile.close();
            std::cout << "Data saved to planner.json" << std::endl;
        } else {
            std::cerr << "Unable to open file: planner.json" << std::endl;
        }
        
    }catch(const std::exception &e){
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

// Day *MealPlanner::getDays()
// {
//     return days;
// }