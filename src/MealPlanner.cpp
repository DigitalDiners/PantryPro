#include "json.hpp"
#include "mealPlanner.h"
#include <fstream>
#include <iostream>
#include <sstream>

using json = nlohmann::json;

MealPlanner::MealPlanner() 
{       
    std::cout << "Constructing meal planner..." << std::endl;

    try{
        std::ifstream jsonFile("./assets/data/planner.json");
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


MealPlanner::~MealPlanner() {
    delete[] days; // Clean up the dynamically allocated memory
}

Day& MealPlanner::getDay(int dayNumber){
    if(dayNumber > 6 || dayNumber < 0){
        std::cout << "Index out of range! Returning monday." << std::endl;
        return days[0];
    }else{
        return days[dayNumber];
    }
}


std::string MealPlanner::getPlannerJson() const{
    return plannerJson;
}

Day* MealPlanner::getDays(){
    return days;
}