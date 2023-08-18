#include "MyApp.h"
#include "databaseConnection.h"
#include "recipeDatabase.h"

int main()
{
    // Example of using the RecipeDatabase class to create an instance of a Recipe object 
    // and return its value

    RecipeDatabase db;
    Recipe myRecipe = db.getRecipeById(38);
    std::cout << "Recipe Name: " << myRecipe.getName() << std::endl;

    MyApp app;
    app.Run();

    return 0;
}
