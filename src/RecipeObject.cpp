/**
 * @file recipe.cpp
 * @author Luke 
 * @brief Class abstraction for recipe objects
 * @version 0.1
 * @date 2023-08-18
 * 
 */

#include <string>

using namespace std;

/**
 * @brief recipe information
 *  Represents information related to a particular recipe in the database.
 *  Upon construction, we pass only the recipe ID.
 *  Once database has been set up, we can get the rest of the information 
 *  about a recipe by passing only the recipe ID.
 * 
 */
class recipeObject
{
private:
    /* data */
    long recipeID;
    string name;
    string prepTime;
    string totalTime;
    string category;
    float calories;
    
public:
    
    explicit recipeObject(long recipeID);

    /**
     * @brief Get the recipe ID of this object
     * 
     * @return long the ID of this object in the database
     */
    long getrecipeID(){
        return recipeID;
    }

    /**
     * @brief Set the Name recipe object
     * 
     * @param name name of the recipe
     */
    void setName(const string name){
        this->name = name;
    }
    /**
     * @brief Get the Name of this recipe object
     * 
     * @return string name of the recipe object
     */
    string getName(){
        return name;
    }

    /**
     * @brief Set the Prep Time of this recipe object
     * 
     *  Prep time is formated as so:
     *      PT45M means Prep-time 45 minutes.
     *      PT24H45M means prep-time 24 hours and 45 minutes.
     * 
     * @param prepTime the time to prepare this recipe
     */
    void setPrepTime(const string prepTime){
        this->prepTime = prepTime;
    }
    /**
     * @brief Get the Prep Time of this recipe
     * 
     * @return string the prep time as a string
     */
    string getPrepTime(){
        return prepTime;
    }

    /**
     * @brief Set the Total Time of this recipe
     *   Total time is formated as so:
     *      PT45M means Prep-time 45 minutes.
     *      PT24H45M means prep-time 24 hours and 45 minutes.
     * 
     * 
     * @param totalTime the total time to make this recipe as a string
     */
    void setTotalTime(const string totalTime){
        this->totalTime = totalTime;
    }
    /**
     * @brief Get the Total Time to make this recipe.
     * 
     * @return string the total time to make this recipe as a string
     */
    string getTotalTime(){
        return totalTime;
    }

    /**
     * @brief Set the Category of this recipe object
     * 
     * @param category the category of this recipe
     */
    void setCategory(const string category){
        this->category = category;
    }
    /**
     * @brief Get the Category of this recipe.
     * 
     * @return string the category of this recipe
     */
    string getCategory(){
        return category;
    }

    /**
     * @brief Set the Calories of this recipe object
     * 
     * @param calories the number of calories in this recipe
     */
    void setCalories(const float calories){
        this->calories = calories;
    }
    /**
     * @brief Get the Calories of this recipe object
     * 
     * @return float the number of calories in this recipe.
     */
    float getCalories(){
        return calories;
    }

};

/**
 * @brief Construct a new recipe:: recipe object
 *  When constructing a recipe object, we pass only the recipe ID, as the rest of the information can be
 *  obtained from the database and assigned when needed/retrieved/available using that recipe ID.
 * 
 * @param recipeID the coded ID of this recipe, as it is represented in the data of the database.
 */
recipeObject::recipeObject(long recipeID)
{
    this->recipeID = recipeID;
}