#include "../src/RecipeObject.cpp"
#include "catch_amalgamated.cpp"

/**
 * @brief First test case for Recipe objects
 *  Testing Constructors, setters and getters.
 */
TEST_CASE( "Check all methods", "[classic]" )  
{
    SECTION("Tests that the constructor works correctly"){
        RecipeObject testRecipe1(1);
        REQUIRE(testRecipe1.getRecipeID() == 1);
        RecipeObject testRecipe2(10202);
        REQUIRE(testRecipe2.getRecipeID() == 10202);
        RecipeObject testRecipe3(777);
        REQUIRE(testRecipe3.getRecipeID() == 777);
    }

    SECTION("Positive tests check the setters and getters work correctly"){
        RecipeObject testRecipe1(1);
        testRecipe1.setName("aaa");
        testRecipe1.setPrepTime("PT10M");
        testRecipe1.setTotalTime("PT10H");
        testRecipe1.setCategory("bbb");
        testRecipe1.setCalories(1000);
        REQUIRE(testRecipe1.getName() == "aaa");
        REQUIRE(testRecipe1.getPrepTime() == "PT10M");
        REQUIRE(testRecipe1.getTotalTime() == "PT10H");
        REQUIRE(testRecipe1.getCategory() == "bbb");
        REQUIRE(testRecipe1.getCalories() == 1000);
    }

    SECTION("Negative test, where applicable"){
        RecipeObject testRecipe1(1);
        testRecipe1.setCalories(1000);
        REQUIRE(testRecipe1.getCalories() != 100);
        REQUIRE(testRecipe1.getCalories() != 10000);
        REQUIRE(testRecipe1.getCalories() != 1);
    }
    
}