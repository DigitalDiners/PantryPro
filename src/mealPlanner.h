#ifndef MEAL_PLANNER_H
#define MEAL_PLANNER_H

#include <vector>
#include "day.h"

class MealPlanner
{
private:
    Day* days;
    std::string plannerJson;

public:
    /**
     * @brief Construct a new meal Planner object
     * @details Once constructed, makes calls to other important classes to provide functionalities.
     * Iterates over all days and assigns the meals for each day as saved in the mealPlanner.json file.
     */
    MealPlanner();

    /**
     * @brief Destroy the Meal Planner object
     * @details destroys day objects.
     */
    ~MealPlanner();
    

    /**
     * @brief Get the Day object by index.
     * 
     * @param dayNumber the day of the week, starting with Monday indexed as 0, through to Sunday indexed as 6.
     * @return Reference to the day object at the specified index.
     */
    Day& getDay(int dayNumber);


    /**
     * @brief Get the Planner Json string object
     * 
     * @return std::string a string that contains the json file contents.
     */
    std::string getPlannerJson() const;

    bool addToPlanner(std::string recipeName, int recipeId, std::string day, std::string meal);



    /**
     * @brief Get the Days vector
     * 
     * @return std::vector<Day> 
     */
    Day* getDays();

    
};

#endif