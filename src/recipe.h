#ifndef RECIPE_H
#define RECIPE_H

#include <string>

/**
 * @class Recipe
 * @brief Represents a cooking recipe with its related details.
 *
 * This class encapsulates the properties of a cooking recipe, such as its name, author,
 * preparation details, and nutritional information.
 */
class Recipe
{
private:
    int recipeId;
    std::string recipeName;
    int authorId;
    std::string authorName;
    int cookTime, prepTime, totalTime;
    std::string datePublished, description, category;
    int calories, servings, yieldQuantity;

    /**
     * @brief Constructs a Recipe object with given properties.
     *
     * @param id Unique identifier for the recipe.
     * @param name Name of the recipe.
     * @param aId Unique identifier for the author of the recipe.
     * @param aName Name of the author.
     * @param cTime Time required for cooking (in minutes).
     * @param pTime Time required for preparation (in minutes).
     * @param tTime Total time (in minutes).
     * @param dPublished Date the recipe was published.
     * @param desc Brief description of the recipe.
     * @param cat Category or type of the recipe.
     * @param cal Caloric content of the recipe.
     * @param serv Number of servings the recipe produces.
     * @param yieldQ Quantity yielded by the recipe.
     */
public:
    Recipe(int id, const std::string &name, int aId, const std::string &aName,
           int cTime, int pTime, int tTime, const std::string &dPublished,
           const std::string &desc, const std::string &cat,
           int cal, int serv, int yieldQ);

    /**
     * @brief Get the unique identifier of the recipe.
     * @return The recipe's ID.
     */
    int getId() const;

    /**
     * @brief Get the name of the recipe.
     * @return The recipe's name.
     */
    std::string getName() const;

    /**
     * @brief Get the unique identifier of the recipe's author.
     * @return The author's ID.
     */
    int getAuthorId() const;

    /**
     * @brief Get the name of the recipe's author.
     * @return The author's name.
     */
    std::string getAuthorName() const;

    /**
     * @brief Get the time required for cooking.
     * @return The cooking time in minutes.
     */
    int getCookTime() const;

    /**
     * @brief Get the time required for preparation.
     * @return The preparation time in minutes.
     */
    int getPrepTime() const;

    /**
     * @brief Get the total time for both cooking and preparation.
     * @return The total time in minutes.
     */
    int getTotalTime() const;

    /**
     * @brief Get the date when the recipe was published.
     * @return The date of publication.
     */
    std::string getDatePublished() const;

    /**
     * @brief Get the description of the recipe.
     * @return The recipe's description.
     */
    std::string getDescription() const;

    /**
     * @brief Get the category or type of the recipe.
     * @return The recipe's category.
     */
    std::string getCategory() const;

    /**
     * @brief Get the caloric content of the recipe.
     * @return The number of calories.
     */
    int getCalories() const;

    /**
     * @brief Get the number of servings the recipe produces.
     * @return The number of servings.
     */
    int getServings() const;

    /**
     * @brief Get the quantity yielded by the recipe.
     * @return The yield quantity.
     */
    int getYieldQuantity() const;
};

#endif // RECIPE_H
