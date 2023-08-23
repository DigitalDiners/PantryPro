#include "recipeImage.h"

RecipeImage::RecipeImage(int recipeId, int imageNumber, const std::string& imageURL):
    recipeId(recipeId), imageNumber(imageNumber), imageURL(imageURL) {}

int RecipeImage::getRecipeId() const {
    return recipeId;
}

int RecipeImage::getImageNumber() const {
    return imageNumber;
}

std::string RecipeImage::getImageURL() const {
    return imageURL;
}


