#include "MyApp.h"
#include "databaseConnection.h"
#include "recipeDatabase.h"

int main()
{
    // Example of using the recipeDatabase class to create an instance of a recipe object 
    // and return its value

    recipeDatabase db;
    recipe myrecipe = db.getrecipeById(38);
    std::cout << "recipe Name: " << myrecipe.getName() << std::endl;

    MyApp app;
    app.Run();

    return 0;
}
