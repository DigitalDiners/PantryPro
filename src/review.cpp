#include "review.h"

Review::Review(int reviewId, int recipeId, int authorId, int rating, const std::string &review, const std::string &dateSubmitted, const std::string &dateModified):
    reviewId(reviewId), recipeId(recipeId), authorId(authorId), rating(rating), review(review), dateSubmitted(dateSubmitted), dateModified(dateModified) {}

int Review::getReviewId() const {
    return reviewId;
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
    return review;
}

std::string Review::getDateSubmitted() const {
    return dateSubmitted;
}

std::string Review::getDateModified() const {
    return dateModified;
}
