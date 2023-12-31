#ifndef RECIPE_OBJECT_H
#define RECIPE_OBJECT_H

#include <string>

/**
 * @brief Class representing a Recipe
 * @details Represents information related to a particular recipe in the database.
 *  Upon construction, we pass only the recipe ID.
 *  Once database has been set up, we can get the rest of the information 
 *  about a recipe by passing only the recipe ID.
 * 
 */
class RecipeObject
{
private:
    /* data */
    int recipeID;
    std::string name;
    std::string prepTime;
    std::string totalTime;
    std::string category;
    float calories;
    
public:
    /**
     * @brief Construct a new recipe:: recipe object
     *  When constructing a recipe object, we pass only the recipe ID, as the rest of the information can be
     *  obtained from the database and assigned when needed/retrieved/available using that recipe ID.
     * 
     * @param recipeID the coded ID of this recipe, as it is represented in the data of the database.
     */
    RecipeObject(int recipeID);

    /**
     * @brief Get the recipe ID of this object
     * 
     * @return long the ID of this object in the database
     */
    int getRecipeID() const;

    /**
     * @brief Set the Name recipe object
     * 
     * @param name name of the recipe
     */
    void setName(const std::string &name);

    /**
     * @brief Get the Name of this recipe object
     * 
     * @return string name of the recipe object
     */
    std::string getName() const;

    /**
     * @brief Set the Prep Time of this recipe object
     * 
     *  Prep time is formated as so:
     *      PT45M means Prep-time 45 minutes.
     *      PT24H45M means prep-time 24 hours and 45 minutes.
     * 
     * @param prepTime the time to prepare this recipe
     */
    void setPrepTime(const std::string &prepTime) ;

    /**
     * @brief Get the Prep Time of this recipe
     * 
     * @return string the prep time as a string
     */
    std::string getPrepTime() const;

    /**
     * @brief Set the Total Time of this recipe
     *   Total time is formated as so:
     *      PT45M means Prep-time 45 minutes.
     *      PT24H45M means prep-time 24 hours and 45 minutes.
     * 
     * 
     * @param totalTime the total time to make this recipe as a string
     */
    void setTotalTime(const std::string &totalTime);

    /**
     * @brief Get the Total Time to make this recipe.
     * 
     * @return string the total time to make this recipe as a string
     */
    std::string getTotalTime() const;

    /**
     * @brief Set the Category of this recipe object
     * 
     * @param category the category of this recipe
     */
    void setCategory(const std::string &category) ;

    /**
     * @brief Get the Category of this recipe.
     * 
     * @return string the category of this recipe
     */
    std::string getCategory() const;

    /**
     * @brief Set the Calories of this recipe object
     * 
     * @param calories the number of calories in this recipe
     */
    void setCalories(float calories) ;

    /**
     * @brief Get the Calories of this recipe object
     * 
     * @return float the number of calories in this recipe.
     */
    float getCalories() const;

};

#endif