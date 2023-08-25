#include "MyApp.h"
#include "databaseConnection.h"
#include "recipeDatabase.h"
#include "recipe.h"
#include "recipeAPI.h"
#include <Ultralight/Ultralight.h>
#include <Ultralight/platform/Config.h>
#include <Ultralight/platform/Platform.h>
#include <Ultralight/Renderer.h>
#include <Ultralight/View.h>
#include <Ultralight/String.h> // Include this for Ultralight String type


int main()
{
    RecipeDatabase db;
    Recipe recipe = db.getRecipeById(38);
    std::cout << "Recipe Name: " << recipe.getName() << std::endl;

    RecipeImage image = db.getRecipeImage(39, 1);
    std::cout << "Recipe Image URL: " << image.getImageURL() << std::endl;

    MyApp app;
    app.Run();

    return 0;
}
