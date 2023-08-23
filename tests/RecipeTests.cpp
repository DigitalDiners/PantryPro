#include "../src/recipeObject.cpp"
#include "catch_amalgamated.cpp"

/**
 * @brief First test case for recipe objects
 *  Testing Constructors, setters and getters.
 */
TEST_CASE( "Check all methods", "[classic]" )  
{
    SECTION("Tests that the constructor works correctly"){
        recipeObject testrecipe1(1);
        REQUIRE(testrecipe1.getrecipeID() == 1);
        recipeObject testrecipe2(10202);
        REQUIRE(testrecipe2.getrecipeID() == 10202);
        recipeObject testrecipe3(777);
        REQUIRE(testrecipe3.getrecipeID() == 777);
    }

    SECTION("Positive tests check the setters and getters work correctly"){
        recipeObject testrecipe1(1);
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
        recipeObject testrecipe1(1);
        testrecipe1.setCalories(1000);
        REQUIRE(testrecipe1.getCalories() != 100);
        REQUIRE(testrecipe1.getCalories() != 10000);
        REQUIRE(testrecipe1.getCalories() != 1);
    }
    
}