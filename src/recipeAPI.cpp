#include "recipeAPI.h"
#include "recipeDatabase.h"

#include <Ultralight/Ultralight.h>
#include <AppCore/JSHelpers.h>
#include <b/Ultralight/View.h>


void RecipeAPI::BindToJS(ultralight::View* view) {
    auto& js_context = view->js_context();
    ultralight::SetJSContext(js_context);
    auto global_object = ultralight::JSGlobalObject();

    // Create our "recipeAPI" JavaScript object.
    ultralight::JSObject recipeAPI;

    recipeAPI["getId"] = ultralight::Bind(RecipeAPI::GetId);
    recipeAPI["getName"] = ultralight::Bind(RecipeAPI::GetName);
    recipeAPI["getAuthorId"] = ultralight::Bind(RecipeAPI::GetAuthorId);
    recipeAPI["getCookTime"] = ultralight::Bind(RecipeAPI::GetCookTime);

    // Add the "recipeAPI" object to the global JS context so it can be accessed from JS.
    global_object["recipeAPI"] = recipeAPI;
}

ultralight::JSValue RecipeAPI::GetId(const ultralight::JSObject&, const ultralight::JSArgs&) {
    Recipe recipe = RecipeDatabase::getRecipeById(1);  // Assuming 1 for demonstration. You might get the ID from JSArgs in a real-world scenario.
    return ultralight::JSValue((int32_t)recipe.getId());
}

ultralight::JSValue RecipeAPI::GetName(const ultralight::JSObject&, const ultralight::JSArgs&) {
    Recipe recipe = RecipeDatabase::getRecipeById(1);
    return ultralight::JSValue(recipe.getName().c_str());
}

ultralight::JSValue RecipeAPI::GetAuthorId(const ultralight::JSObject&, const ultralight::JSArgs&) {
    Recipe recipe = RecipeDatabase::getRecipeById(1);
    return ultralight::JSValue((int32_t)recipe.getAuthorId());
}

ultralight::JSValue RecipeAPI::GetCookTime(const ultralight::JSObject&, const ultralight::JSArgs&) {
    Recipe recipe = RecipeDatabase::getRecipeById(1);
    return ultralight::JSValue((int32_t)recipe.getCookTime());
}
