#ifndef DAY_H
#define DAY_H
#include <iostream>
#include "recipeObject.h"

/**
 * @brief Class representing one of the days of the week.
 * @details Abstracts out the day of the week and holds references to certain
 *  RecipeObjects.
 */
class Day
{
private:
    int dayNumber;
    std::string dayName;
    RecipeObject* breakfastPtr;
    RecipeObject* lunchPtr;
    RecipeObject* dinnerPtr;

public:
    
    /**
     * @brief Construct a new Day object
     * @details Day objects used to represent each day of the week. 
     *  Stores recipes for each meal of that day
     * @param dayNumber the day of the week, starting from 0.
     */
    Day(int dayNumber);

    /**
     * @brief Set the Day Name
     * @details Sets the name of this day object, uses the int passed when constructed.
     *  Should be called inside the constructor.
     */
    void setDayName();

    /**
     * @brief Set a recipe into a meal slot of this object
     * 
     * @param recipe the recipe to added to this slot
     * @param meal the meal number, 0 for breakfast, 1 for lunch, 2 for dinner
     */
    void setMeal(RecipeObject &recipe, int meal);

    /**
     * @brief Get the Meals Array of this object
     * 
     * @return RecipeObject* ptr to breakfast
     */
    RecipeObject* getBreakfast() const;

    /**
     * @brief Get the Meals Array of this object
     * 
     * @return RecipeObject* ptr to the lunch datafield
     */
    RecipeObject* getLunch() const;

    /**
     * @brief Get the Dinner meal
     * 
     * @return RecipeObject* ptr to dinner datafield
     */
    RecipeObject* getDinner() const;

    /**
     * @brief Get the Day Num object
     * 
     * @return int the number representing this day of the week
     */
    int getDayNumber() const;

    void clearMeal(int meal);

    /**
     * @brief Get the Day Name object
     * 
     * @return string the name of this day of the week
     */
    std::string getDayName() const;

};

#endif