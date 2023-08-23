#include "MyApp.h"
#include "databaseConnection.h"
#include "recipeDatabase.h"
#include "recipe.h"

int main()
{
    // Example of using the RecipeDatabase class to create an instance of a Recipe object 
    // and return its value

    RecipeDatabase db;
    Recipe recipe = db.getRecipeById(38);
    std::cout << "Recipe Name: " << recipe.getName() << std::endl;

    RecipeImage image = db.getRecipeImage(39, 1);
    std::cout << "Recipe Image URL: " << image.getImageURL() << std::endl;

    MyApp app;
    app.Run();

    return 0;
}
