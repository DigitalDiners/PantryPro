#include "MyApp.h"
#include "databaseConnection.h"
#include "recipeDatabase.h"
#include "recipe.h"
#include "recipeAPI.h"

int main()
{
    // Example of using the RecipeDatabase class to create an instance of a Recipe object 
    // and return its value
    ultralight::RefPtr<ultralight::Platform> platform = ultralight::Platform::Create();
    ultralight::RefPtr<ultralight::Renderer> renderer = ultralight::Renderer::Create();

    ultralight::RefPtr<ultralight::View> view = ultralight::View::Create(renderer.get(), 800, 600, false);
    ultralight::RefPtr<ultralight::Overlay> overlay = ultralight::Overlay::Create(*view, 800, 600, 0, 0);

    RecipeAPI recipeApi; // Instantiate your C++ class

    overlay->view()->SetJSContextGlobalObject("RecipeAPI", &recipeApi); // Expose the C++ object to JavaScript
    overlay->view()->LoadURL("your_html_file.html");

    RecipeDatabase db;
    Recipe recipe = db.getRecipeById(38);
    std::cout << "Recipe Name: " << recipe.getName() << std::endl;

    RecipeImage image = db.getRecipeImage(39, 1);
    std::cout << "Recipe Image URL: " << image.getImageURL() << std::endl;

    MyApp app;
    app.Run();

    return 0;
}
