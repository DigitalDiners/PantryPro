#include "MyApp.h"
#include "databaseConnection.h"
#include "recipeDatabase.h"
#include "recipe.h"
#include "review.h"



int main()
{
    // Example of using the recipeDatabase class to create an instance of a recipe object
    // and return its name and instructions
    std::cout << "-------------" << std::endl;
    RecipeDatabase db;
    Recipe recipe = db.getRecipeById(524);
    std::cout << "Recipe Name: " << recipe.getName() << std::endl;

    std::cout << "-------------" << std::endl;
    std::cout << "Recipe Instructions: " << recipe.getInstructions() << std::endl;

    // Example of using the RecipeDatabase class to create an instance of a RecipeImage object
    std::cout << "-------------" << std::endl;
    RecipeImage image = db.getRecipeImage(524, 1);
    std::cout << "Recipe Image URL: " << image.getImageURL() << std::endl;

    // Example of using the RecipeDatabase class to create an instance of a vector of Review objects
    std::cout << "-------------" << std::endl;
    std::cout << "Reviews:" << std::endl;
    std::cout << "-------------" << std::endl;
    std::vector<Review> reviews = db.getReviewsByRecipeId(40);
    for (const Review &r : reviews) {
        std::cout << "Review ID: " << r.getReviewId() << std::endl;
        std::cout << "Recipe ID: " << r.getRecipeId() << std::endl;
        std::cout << "Author ID: " << r.getAuthorId() << std::endl;
        std::cout << "Rating: " << r.getRating() << std::endl;
        std::cout << "Text: " << r.getReviewText() << std::endl;
        std::cout << "Submitted: " << r.getDateSubmitted() << std::endl;
        std::cout << "Modified: " << r.getDateModified() << std::endl;
        std::cout << "-------------" << std::endl;
    }

    MyApp app;
    app.Run();

    return 0;
}
