#include "recipe.cpp"

/**
 * @brief Class representing one of the days of the week.
 * 
 */
class day
{
private:
    int dayNumber;
    string dayName;
    recipe breakfast;
    recipe lunch;
    recipe dinner;
    Reicpe meals[];
public:
    day(int dayNumber);

    /**
     * @brief Set the Day Name
     *  Sets the name of this day object, uses the int passed when constructed.
     */
    void setDayName(){
        switch (dayNumber)
        {
        case 0:
            dayName = "Monday";
            break;
        case 1:
            dayName = "Tuesday";
            break;
        case 2:
            dayName = "Wednesday";
            break;
        case 3:
            dayName = "Thursday";
            break;
        case 4:
            dayName = "Friday";
            break;
        case 5:
            dayName = "Saturday";
            break;
        case 6:
            dayName = "Sunday";
            break;
        default:
            throw (100)
            break;
        }
    }

    /**
     * @brief Set a recipe into a meal slot of this object
     * 
     * @param recipe the recipe to added to this slot
     * @param meal the meal number
     */
    void setMeal(recipe recipe, int meal){
        if(meal > 2){
            throw meal 
        }
        switch (meal)
        {
        case 0:
            this->breakfast = recipe;
            break;
        case 1:
            this->lunch = recipe;
            break;
        case 2:
            this->dinner = recipe;
            break;
        default:
            break;
        }
    }

    /**
     * @brief Get the Meals Array of this object
     * 
     * @return recipe[] All the meals in this day
     */
    Recipe[] getMealsArray(){
        return {breakfast, lunch, dinner};
    }

    /**
     * @brief Get the Day Num object
     * 
     * @return int the number representing this day of the week
     */
    int getDayNum(){
        return this->dayNumber;
    }

    /**
     * @brief Get the Day Name object
     * 
     * @return string the name of this day of the week
     */
    string getDayName(){
        return this.dayName;
    }

};

/**
 * @brief Construct a new day::day object
 * 
 * @param dayNumber the day of the week, starting from 0.
 */
day::day(int dayNumber)
{
    if(dayNumber < 8 && dayNumber => 0){
        this->dayNumber = dayNumber;
        setDayName();
    }else{
        throw dayNumber
    }
}
    

