#include "review.h"

Review::Review(int reviewId, int recipeId, int authorId, int rating, const std::string &reviewText, const std::string &dateSubmitted, const std::string &dateModified):
    reviewId(reviewId), recipeId(recipeId), authorId(authorId), rating(rating), reviewText(reviewText), dateSubmitted(dateSubmitted), dateModified(dateModified) {}

int Review::getReviewId() const {
    return recipeId;
}

int Review::getRecipeId() const {
    return recipeId;
}

int Review::getAuthorId() const {
    return authorId;
}

int Review::getRating() const {
    return rating;
}

std::string Review::getReviewText() const {
    return reviewText;
}

std::string Review::getDateSubmitted() const {
    return dateSubmitted;
}

std::string Review::getDateModified() const {
    return dateModified;
}
