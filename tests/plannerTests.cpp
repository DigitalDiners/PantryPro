#include "catch_amalgamated.cpp"
#include "../src/day.cpp"
#include "../src/recipeObject.cpp"

TEST_CASE("Day objects instantiate correctly for day name", "[classic]")
{
    GIVEN("These instances of day")
    {
        Day monday(0);
        Day tuesday(1);
        Day wednesday(2);
        Day thursday(3);
        Day friday(4);
        Day saturday(5);
        Day sunday(6);

        THEN("Should update name datafields correctly"){
            REQUIRE(monday.getDayName() == "Monday");
            REQUIRE(tuesday.getDayName() == "Tuesday");
            REQUIRE(wednesday.getDayName() == "Wednesday");
            REQUIRE(thursday.getDayName() == "Thursday");
            REQUIRE(friday.getDayName() == "Friday");
            REQUIRE(saturday.getDayName() == "Saturday");
            REQUIRE(sunday.getDayName() == "Sunday");
        }

    }
}

TEST_CASE("Day objects instantiate correctly for day number", "[classic]")
{
    GIVEN("These instances of day")
    {
        Day monday(0);
        Day tuesday(1);
        Day wednesday(2);
        Day thursday(3);
        Day friday(4);
        Day saturday(5);
        Day sunday(6);

        THEN("Should update number datafields correctly"){
            REQUIRE(monday.getDayNumber() == 0);
            REQUIRE(tuesday.getDayNumber() == 1);
            REQUIRE(wednesday.getDayNumber() == 2);
            REQUIRE(thursday.getDayNumber() == 3);
            REQUIRE(friday.getDayNumber() == 4);
            REQUIRE(saturday.getDayNumber() == 5);
            REQUIRE(sunday.getDayNumber() == 6);

        }
    }
}

TEST_CASE("Assigning recipes to the datafields", "[classic]")
{
    GIVEN("This instance of day and recipes")
    {
        Day monday(0);
        
        RecipeObject recipe1(100);
        RecipeObject recipe2(50);
        RecipeObject recipe3(2500);

        monday.setMeal(recipe1, 0);
        monday.setMeal(recipe2, 1);
        monday.setMeal(recipe3, 2);

        THEN("Should assign to the correct datafields"){
            RecipeObject breakfast = *monday.getBreakfast();
            RecipeObject lunch = *monday.getLunch();
            RecipeObject dinner = *monday.getDinner();
            REQUIRE(breakfast.getRecipeID() == recipe1.getRecipeID());
            REQUIRE(lunch.getRecipeID() == recipe2.getRecipeID());
            REQUIRE(dinner.getRecipeID() == recipe3.getRecipeID());
        }

    }
}