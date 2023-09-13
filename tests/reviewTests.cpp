#include "catch_amalgamated.cpp"
#include "../src/review.cpp"
#include <string>

TEST_CASE("Review tests, positive cases", "[classic]"){
    GIVEN("This test instance of Review"){
        //int reviewId, int recipeId, int authorId, int rating, 
        // const std::string &review, const std::string &dateSubmitted, const std::string &dateModified
        int reviewId = 1;
        int recipeId = 54;
        int authorId = 12;
        int rating = 5;
        std::string reviewString = "Amazing!";
        std::string dateSubmitted = "2001-10-17";
        std::string dateModified = "2001-10-17";

        Review testReview(reviewId, recipeId, authorId, rating, reviewString, dateSubmitted, dateModified);

        THEN("Should have all the same values"){
            REQUIRE(testReview.getReviewId() == 1);
            REQUIRE(testReview.getRecipeId() == 54);
            REQUIRE(testReview.getAuthorId() == 12);
            REQUIRE(testReview.getRating() == 5);
            REQUIRE(testReview.getReviewText() == "Amazing!");
            REQUIRE(testReview.getDateSubmitted() == "2001-10-17");
            REQUIRE(testReview.getDateModified() == "2001-10-17");

        }
    }
}

TEST_CASE("Review tests, negative cases", "[classic]"){
    GIVEN("This test instance of Review"){
        //int reviewId, int recipeId, int authorId, int rating, 
        // const std::string &review, const std::string &dateSubmitted, const std::string &dateModified
        int reviewId = 1;
        int recipeId = 54;
        int authorId = 12;
        int rating = 5;
        std::string reviewString = "Amazing!";
        std::string dateSubmitted = "2001-10-17";
        std::string dateModified = "2001-10-17";

        Review testReview(reviewId, recipeId, authorId, rating, reviewString, dateSubmitted, dateModified);

        THEN("Should have all the same values"){
            REQUIRE(testReview.getReviewId() != 111);
            REQUIRE(testReview.getRecipeId() != 544);
            REQUIRE(testReview.getAuthorId() != 1122);
            REQUIRE(testReview.getRating() != 123);
            REQUIRE(testReview.getReviewText() != "terrible...");
            REQUIRE(testReview.getDateSubmitted() != "20asdff");
            REQUIRE(testReview.getDateModified() != "2asf");

        }
    }
}