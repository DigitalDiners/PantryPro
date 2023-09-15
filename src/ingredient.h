#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

/**
 * @class Ingredient
 * @brief Represents an ingredient.
 *
 * This class contains the properties of an ingredient.
 * 
 */
class Ingredient {
private:
    int ingredientId;
    std::string ingredientName;

    /**
     * @brief Constructs an image object with given properties.
     * 
     * @param ingredientId Unique identifier for the ingredient.
     * @param ingredientName The name of the ingredient.
     * 
     */
public:
    Ingredient(int ingredientId, const std::string &ingredientName);

    /**
     * @brief Get the unique identifier of the ingredient.
     * @return The ingredient's ID.
     */
    int getIngredientId() const;

    /**
     * @brief Get the name of the recipe.
     * @return The ingredient's ID.
     */
    std::string getIngredientName() const;


};

#endif // INGREDIENT_H