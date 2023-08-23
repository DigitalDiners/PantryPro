#ifndef REVIEW_H
#define REVIEW_H

#include <string>

/**
 * @class Review
 * @brief Represents a review of the recipe.
 *
 * This class contains the properties of a review of a recipe, such as its author's name and rating.
 * 
 */
class Review
{
private:
    int reviewId;
    int recipeId;
    int authorId;
    int rating;
    std::string review;
    std::string dateSubmitted;
    std::string dateModified;

    /**
     * @brief Constructs an image object with given properties.
     * 
     * @param reviewId Unique identifier for the recipe.
     * @param recipeId The number of the image asscoiated with a recipe.
     * @param authorId The id associated with the author of the review.
     * @param rating The rating of the review given by the author.
     * @param review The text of the review written by the author.
     * @param dateSubmitted The date the review was submitted.
     * @param dateModified The date the review was modified.
     * 
     */
public:
    Review(int reviewId, int recipeId, int authorId, int rating, const std::string &review, const std::string &dateSubmitted, const std::string &dateModified);

    /**
     * @brief Get the unique identifier of the recipe.
     * @return The recipe's ID.
     */
    int getReviewId() const;

    /**
     * @brief Get the unique identifier of the recipe.
     * @return The recipe's ID.
     */
    int getRecipeId() const;

    /**
     * @brief Get the unique identifier of the author.
     * @return The author's ID.
     */
    int getAuthorId() const;

    /**
     * @brief Get the rating of the review.
     * @return The review's rating.
     */
    int getRating() const;

    /**
     * @brief Get the text of the review.
     * @return The review's text.
     */
    std::string getReviewText() const;

    /**
     * @brief Get the date the review was submitted.
     * @return The review's date submitted.
     */
    std::string getDateSubmitted() const;

    /**
     * @brief Get the date the review was modified.
     * @return The review's date modified.
     */
    std::string getDateModified() const;

};

#endif // REVIEW_H