#include "mealPlanner.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "recipe.h"


MealPlanner::MealPlanner()
:recipeVector(7, std::vector<int>(3))
{
    for(std::vector<int> days:recipeVector){
        for(int meals:days){
            meals = 0;
        }
    }
    std::cout << recipeVector.size() << std::endl;
    std::cout << recipeVector[0][2] << std::endl;
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
    std::string plannerJson;
    std::cout << "planner string made" << std::endl;
    plannerJson +="[{\"name\":\"Monday\", \"breakfast\":\""+name(recipeVector[0][0])+"\", \"lunch\": \""+name(recipeVector[0][1])+"\", \"dinner\": \""+name(recipeVector[0][2])+"\"}";
    plannerJson +=",{\"name\":\"Tuesday\", \"breakfast\":\""+name(recipeVector[1][0])+"\", \"lunch\": \""+name(recipeVector[1][1])+"\", \"dinner\": \""+name(recipeVector[1][2])+"\"}";
    plannerJson +=",{\"name\":\"Wednesday\", \"breakfast\":\""+name(recipeVector[2][0])+"\", \"lunch\": \""+name(recipeVector[2][1])+"\", \"dinner\": \""+name(recipeVector[2][2])+"\"}";
    plannerJson +=",{\"name\":\"Thursday\", \"breakfast\":\""+name(recipeVector[3][0])+"\", \"lunch\": \""+name(recipeVector[3][1])+"\", \"dinner\": \""+name(recipeVector[3][2])+"\"}";
    plannerJson +=",{\"name\":\"Friday\", \"breakfast\":\""+name(recipeVector[4][0])+"\", \"lunch\": \""+name(recipeVector[4][1])+"\", \"dinner\": \""+name(recipeVector[4][2])+"\"}";
    plannerJson +=",{\"name\":\"Saturday\", \"breakfast\":\""+name(recipeVector[5][0])+"\", \"lunch\": \""+name(recipeVector[5][1])+"\", \"dinner\": \""+name(recipeVector[5][2])+"\"}";
    plannerJson +=",{\"name\":\"Sunday\", \"breakfast\":\""+name(recipeVector[6][0])+"\", \"lunch\": \""+name(recipeVector[6][1])+"\", \"dinner\": \""+name(recipeVector[6][2])+"\"}";
    
    plannerJson += "]";


    std::cout << plannerJson << std::endl;
    return plannerJson;
}

// Day *MealPlanner::getDays()
// {
//     return days;
// }