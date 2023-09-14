#include "MyApp.h"
#include "recipe.h"
#include "recipeDatabase.h"

#include <AppCore/JSHelpers.h>
#include <Ultralight/Ultralight.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800


MyApp::MyApp()
{
  ///
  /// Create our main App instance.
  ///
  app_ = App::Create();

  ///
  /// Create a resizable window by passing by OR'ing our window flags with
  /// kWindowFlags_Resizable.
  ///
  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
                           false, kWindowFlags_Titled | kWindowFlags_Resizable);

  ///
  /// Create our HTML overlay-- we don't care about its initial size and
  /// position because it'll be calculated when we call OnResize() below.
  ///
  overlay_ = Overlay::Create(window_, 1, 1, 0, 0);

  ///
  /// Force a call to OnResize to perform size/layout of our overlay.
  ///
  OnResize(window_.get(), window_->width(), window_->height());

  ///
  /// Load a page into our overlay's View
  ///
  overlay_->view()->LoadURL("file:///app.html");

  ///
  /// Register our MyApp instance as an AppListener so we can handle the
  /// App's OnUpdate event below.
  ///
  app_->set_listener(this);

  ///
  /// Register our MyApp instance as a WindowListener so we can handle the
  /// Window's OnResize event below.
  ///
  window_->set_listener(this);

  ///
  /// Register our MyApp instance as a LoadListener so we can handle the
  /// View's OnFinishLoading and OnDOMReady events below.
  ///
  overlay_->view()->set_load_listener(this);

  ///
  /// Register our MyApp instance as a ViewListener so we can handle the
  /// View's OnChangeCursor and OnChangeTitle events below.
  ///
  overlay_->view()->set_view_listener(this);
}

MyApp::~MyApp()
{
}

void MyApp::Run()
{
  app_->Run();
}

void MyApp::OnUpdate()
{
  ///
  /// This is called repeatedly from the application's update loop.
  ///
  /// You should update any app logic here.
  ///
}

void MyApp::OnClose(ultralight::Window *window)
{
  app_->Quit();
}

void MyApp::OnResize(ultralight::Window *window, uint32_t width, uint32_t height)
{
  ///
  /// This is called whenever the window changes size (values in pixels).
  ///
  /// We resize our overlay here to take up the entire window.
  ///
  overlay_->Resize(width, height);
}

void MyApp::OnFinishLoading(ultralight::View *caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String &url)
{
  ///
  /// This is called when a frame finishes loading on the page.
  ///
}

std::string MyApp::removeQuotes(const std::string& input) {
    std::string result = input;
    result.erase(std::remove(result.begin(), result.end(), '\"'), result.end());
    return result;
}

std::string MyApp::convertRecipesToJson(const std::vector<Recipe>& recipes) {
    std::cout << "convertRecipesToJson called" << std::endl;
    std::string json = "[";

    std::cout << "recipes.size(): " << recipes.size() << std::endl;
    for (const Recipe& recipe : recipes) {
        std::cout << "recipe: " << recipe.getName() << std::endl;
        json += "{ ";
        json += "\"recipeId\": " + removeQuotes(std::to_string(recipe.getId())) + ",";
        json += "\"recipeName\": \"" + removeQuotes(recipe.getName()) + "\",";
        json += "\"authorId\": " + removeQuotes(std::to_string(recipe.getAuthorId())) + ",";
        json += "\"cookTime\": " + removeQuotes(std::to_string(recipe.getCookTime())) + ",";
        json += "\"prepTime\": " + removeQuotes(std::to_string(recipe.getPrepTime())) + ",";
        json += "\"totalTime\": " + removeQuotes(std::to_string(recipe.getTotalTime())) + ",";
        json += "\"datePublished\": \"" + removeQuotes(recipe.getDatePublished()) + "\",";
        json += "\"category\": \"" + removeQuotes(recipe.getCategory()) + "\",";
        json += "\"calories\": " + removeQuotes(std::to_string(recipe.getCalories())) + ",";
        json += "\"servings\": " + removeQuotes(std::to_string(recipe.getServings())) + ",";
        json += "\"yieldQuantity\": " + removeQuotes(std::to_string(recipe.getYieldQuantity()));

        if (json.back() == ',') json.pop_back(); 
        json += " },";
    }
    if (json.back() == ',') json.pop_back();
    json += "]";

    return json;
}

JSValue MyApp::SearchRecipes(const JSObject& thisObject, const JSArgs& args) {
    std::cout << "SearchRecipes called" << std::endl;

    std::vector<std::string> ingredients;
    if (args[0].IsArray()) {
        JSArray ingredientArray = args[0].ToArray();
        for (size_t i = 0; i < ingredientArray.length(); i++) {
            ultralight::String jsStr = ingredientArray[i].ToString();
            ingredients.push_back(std::string(jsStr.utf8().data()));
        }
    }

    RecipeDatabase recipeDB;
    std::vector<Recipe> recipes = recipeDB.getRecipesBySearch(ingredients);
    std::string jsonRecipes = convertRecipesToJson(recipes);

    std::cout << "jsonRecipes: " << jsonRecipes.c_str() << std::endl;

    return JSValue(jsonRecipes.c_str());
}

JSValue MyApp::RecipeIngredients(const JSObject& thisObject, const JSArgs& args){
  std::cout<<"Recipe ingredients called"<< std::endl;

  int recipeId;
  // std::cout<<recipeId<<std::endl;
      std::vector<std::string> ingredients;
    if (args[0].IsArray()) {
        JSArray ingredientArray = args[0].ToArray();
        for (size_t i = 0; i < ingredientArray.length(); i++) {
            ultralight::String jsStr = ingredientArray[i].ToString();
            ingredients.push_back(std::string(jsStr.utf8().data()));
        }
    }

  
    RecipeDatabase recipeDB;
    std::vector<std::string> missingIngredients = recipeDB.getIngredients(recipeId,ingredients);

    std::string json = "[{";
    for(const std::string& ingredient: missingIngredients){
      json += ingredient;
      json += ",";
      std::cout<<ingredient<<std::endl;
    }
    json += "}]";
    // std::string jsonRecipes = convertRecipesToJson(recipes);
    return JSValue(json.c_str());

}

void MyApp::OnDOMReady(ultralight::View *caller,
                uint64_t frame_id,
                bool is_main_frame,
                const String &url) {
  std::cout << "OnDOMReady called" << std::endl;
  ///
  /// Set our View's JSContext as the one to use in subsequent JSHelper calls
  ///
  RefPtr<JSContext> context = caller->LockJSContext();
  SetJSContext(context->ctx());

  JSObject global = JSGlobalObject();

  global["SearchRecipes"] = BindJSCallbackWithRetval(&MyApp::SearchRecipes);
  global["RecipeIngredients"] = BindJSCallbackWithRetval(&MyApp::RecipeIngredients);
}

void MyApp::OnChangeCursor(ultralight::View *caller,
                           Cursor cursor)
{
  ///
  /// This is called whenever the page requests to change the cursor.
  ///
  /// We update the main window's cursor here.
  ///
  window_->SetCursor(cursor);
}

void MyApp::OnChangeTitle(ultralight::View *caller,
                          const String &title)
{
  ///
  /// This is called whenever the page requests to change the title.
  ///
  /// We update the main window's title here.
  ///
  window_->SetTitle(title.utf8().data());
}
