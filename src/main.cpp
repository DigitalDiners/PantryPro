#include "MyApp.h"
#include "databaseConnection.h"
#include "recipeDatabase.h"
#include "recipe.h"

int main()
{
    // Example of using the RecipeDatabase class to create an instance of a Recipe object
    // and return its value

    RecipeDatabase db;
    Recipe recipe = db.getRecipeById(40);
    std::cout << "Recipe Name: " << recipe.getName() << std::endl;

    // Example of using the RecipeDatabase class to create an instance of a RecipeImage object

    RecipeImage image = db.getRecipeImage(40, 1);
    std::cout << "Recipe Image URL: " << image.getImageURL() << std::endl;

    // Example of using the RecipeDatabase class to create an instance of a vector of Review objects

    std::vector<Review> reviews = db.getReviewsByRecipeId(40);

    std::cout << "-------------" << std::endl;
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
