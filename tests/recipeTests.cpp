#include "../src/recipeObject.h"
#include "../src/recipeObject.cpp"
#include "../src/recipeImage.cpp"
#include "catch_amalgamated.cpp"

/**
 * @brief Test case for recipe objects
 * @details Test case for RecipeObject.cpp constructors, setters and getters.
 */
TEST_CASE( "Check all methods", "[classic]" )  
{   
    SECTION("Tests that the constructor works correctly"){
        RecipeObject testrecipe1(1);
        REQUIRE(testrecipe1.getRecipeID() == 1);
        RecipeObject testrecipe2(10202);
        REQUIRE(testrecipe2.getRecipeID() == 10202);
        RecipeObject testrecipe3(777);
        REQUIRE(testrecipe3.getRecipeID() == 777);
    }

    SECTION("Positive tests check the setters and getters work correctly"){
        RecipeObject testrecipe1(1);
        testrecipe1.setName("aaa");
        testrecipe1.setPrepTime("PT10M");
        testrecipe1.setTotalTime("PT10H");
        testrecipe1.setCategory("bbb");
        testrecipe1.setCalories(1000);
        REQUIRE(testrecipe1.getName() == "aaa");
        REQUIRE(testrecipe1.getPrepTime() == "PT10M");
        REQUIRE(testrecipe1.getTotalTime() == "PT10H");
        REQUIRE(testrecipe1.getCategory() == "bbb");
        REQUIRE(testrecipe1.getCalories() == 1000);
    }

    SECTION("Negative test, where applicable"){
        RecipeObject testrecipe1(1);
        testrecipe1.setCalories(1000);
        REQUIRE(testrecipe1.getCalories() != 100);
        REQUIRE(testrecipe1.getCalories() != 10000);
        REQUIRE(testrecipe1.getCalories() != 1);
    }
    
}

/**
 * @brief Tests for recipeImage.cpp
 * @details Checking constructors working correctly. 
 */
TEST_CASE( "Check that recipeImage returns expected values", "[classic]")
{
    SECTION("Positive tests checking getters after construction")
    {
        GIVEN("This instance of recipe image")
        {
            RecipeImage testRecipeImage(1, 1, "imageURL");
    
            THEN("The datafields should be set, and getters return the correct values"){
                REQUIRE(testRecipeImage.getRecipeId() == 1);
                REQUIRE(testRecipeImage.getImageNumber() == 1);
                REQUIRE(testRecipeImage.getImageURL() == "imageURL");

            }
        }
        GIVEN("This instance of recipe image")
        {
            RecipeImage testRecipeImage(10001,5,"anotherURL");

            THEN("The datafields should be set, and getters return the correct values"){
                REQUIRE(testRecipeImage.getRecipeId() == 10001);
                REQUIRE(testRecipeImage.getImageNumber() == 5);
                REQUIRE(testRecipeImage.getImageURL() == "anotherURL");

            }
        }
    }
}
