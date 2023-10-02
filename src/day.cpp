#include "day.h"

Day::Day(int dayNumber)
{
    if(dayNumber < 8 && dayNumber > -1){
        this->dayNumber = dayNumber;
        setDayName();
    }else{
        std::cout << "Not a valid number for day" << std::endl;
    }
}

void Day::setDayName(){
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
        throw (101);
        break;
    }
}

void Day::setMeal(RecipeObject &recipe, int meal){
    if(meal > 2){
        throw meal;
    }
    switch (meal){
    case 0:
        this->breakfastPtr = &recipe;
        break;
    case 1:
        this->lunchPtr = &recipe;
        break;
    case 2:
        this->dinnerPtr = &recipe;
        break;
    default:
        break;
    }
}


RecipeObject* Day::getBreakfast() const{
    return this->breakfastPtr;
}

RecipeObject* Day::getLunch() const{
    return this->lunchPtr;
}

RecipeObject* Day::getDinner() const{
    return this->dinnerPtr;
}

int Day::getDayNumber() const{
    return this->dayNumber;
}

std::string Day::getDayName() const{
    return this->dayName;
}
