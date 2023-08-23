#ifndef RECIPEIMAGE_H
#define RECIPEIMAGE_H

#include <string>

/**
 * @class RecipeImage
 * @brief Represents an image of the recipe.
 *
 * This class contains the properties of an image of a recipe, such as its ID and URL.
 * 
 */
class RecipeImage
{
private:
    int recipeId;
    int imageNumber;
    std::string imageURL;

    /**
     * @brief Constructs an image object with given properties.
     * 
     * @param recipeId Unique identifier for the recipe.
     * @param imageNumber The number of the image asscoiated with a recipe.
     * @param imageURL URL of the image.
     * 
     */
public:
    RecipeImage(int recipeId, int imageNumber, const std::string &imageURL);

    /**
     * @brief Get the unique identifier of the recipe.
     * @return The recipe's ID.
     */
    int getRecipeId() const;

    /**
     * @brief Get the number of the recipe image.
     * @return The image's number.
     */
    int getImageNumber() const;

    /**
     * @brief Get the URL of the image.
     * @return The image's URL.
     */
    std::string getImageURL() const;

};

#endif // RECIPEIMAGE_H