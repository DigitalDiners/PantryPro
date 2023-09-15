#include "../src/recipeObject.cpp"
#include "../src/recipeImage.cpp"
#include "../src/recipe.cpp"
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

TEST_CASE("Testing the other recipe class in our implementation, positive cases","[classic]"){
    GIVEN("This instance of Recipe"){
        //     Recipe(int id, const std::string &name, int aId,
        //    int cTime, int pTime, int tTime, const std::string &dPublished,
        //    const std::string &desc, const std::string &cat,
        //    int cal, int serv, int yieldQ, const std::string &instructions);
        int id = 54;
        std::string name = "Carrot Cake";
        int aId = 1255;
        int cTime = 1;
        int pTime = 2;
        int tTime = 3;
        std::string dPublished = "At the dawn of time";
        std::string desc = "Delicious cake!";
        std::string cat = "Great";
        int cal = 100;
        int serv = 1;
        int yieldQ = 1;
        std::string instructions = "abc123";

        Recipe testRecipe(id, name, aId, cTime, pTime, tTime, dPublished, desc, cat, cal, serv, yieldQ, instructions);

        THEN("These assertions should all pass"){
            REQUIRE(testRecipe.getId() == 54);
            REQUIRE(testRecipe.getName() == "Carrot Cake");
            REQUIRE(testRecipe.getAuthorId() == 1255);
            REQUIRE(testRecipe.getCookTime() == 1);
            REQUIRE(testRecipe.getPrepTime() == 2);
            REQUIRE(testRecipe.getTotalTime() == 3);
            REQUIRE(testRecipe.getDatePublished() == "At the dawn of time");
            REQUIRE(testRecipe.getDescription() == "Delicious cake!");
            REQUIRE(testRecipe.getCategory() == "Great");
            REQUIRE(testRecipe.getCalories() == 100);
            REQUIRE(testRecipe.getServings() == 1);
            REQUIRE(testRecipe.getYieldQuantity() == 1);
            REQUIRE(testRecipe.getInstructions() == "abc123");
        }
    }
}

TEST_CASE("Testing the other recipe class in our implementation, Negative cases","[classic]"){
    GIVEN("This instance of Recipe"){
        //     Recipe(int id, const std::string &name, int aId,
        //    int cTime, int pTime, int tTime, const std::string &dPublished,
        //    const std::string &desc, const std::string &cat,
        //    int cal, int serv, int yieldQ, const std::string &instructions);
        int id = 54;
        std::string name = "Carrot Cake";
        int aId = 1255;
        int cTime = 1;
        int pTime = 2;
        int tTime = 3;
        std::string dPublished = "At the dawn of time";
        std::string desc = "Delicious cake!";
        std::string cat = "Great";
        int cal = 100;
        int serv = 1;
        int yieldQ = 1;
        std::string instructions = "abc123";

        Recipe testRecipe(id, name, aId, cTime, pTime, tTime, dPublished, desc, cat, cal, serv, yieldQ, instructions);

        THEN("These assertions should all pass"){
            REQUIRE(testRecipe.getId() != 512);
            REQUIRE(testRecipe.getName() != "Carrots");
            REQUIRE(testRecipe.getAuthorId() != 121);
            REQUIRE(testRecipe.getCookTime() != 1124);
            REQUIRE(testRecipe.getPrepTime() != 212);
            REQUIRE(testRecipe.getTotalTime() != 2);
            REQUIRE(testRecipe.getDatePublished() != "AtNEVER");
            REQUIRE(testRecipe.getDescription() != "Delicioasf");
            REQUIRE(testRecipe.getCategory() != "Gafssffght");
            REQUIRE(testRecipe.getCalories() != 10);
            REQUIRE(testRecipe.getServings() != 1123);
            REQUIRE(testRecipe.getYieldQuantity() != 112);
            REQUIRE(testRecipe.getInstructions() != "abcasfa123");
        }
    }
}
