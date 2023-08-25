#include "MyApp.h"
#include "recipe.h"
#include "recipeDatabase.h"

#include <AppCore/JSHelpers.h>
#include <Ultralight/Ultralight.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

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


std::string MyApp::convertRecipesToJson(const std::vector<Recipe>& recipes) {
    std::cout << "convertRecipesToJson called" << std::endl;
    std::string json = "[";

    std::cout << "recipes.size(): " << recipes.size() << std::endl;
    for (const Recipe& recipe : recipes) {
        std::cout << "recipe: " << recipe.getName() << std::endl;
        json += "{ ";
        json += "\"recipeId\": " + std::to_string(recipe.getId()) + ",";
        json += "\"recipeName\": \"" + recipe.getName() + "\",";
        json += "\"authorId\": " + std::to_string(recipe.getAuthorId()) + ",";

        json += "\"cookTime\": " + std::to_string(recipe.getCookTime()) + ",";
        json += "\"prepTime\": " + std::to_string(recipe.getPrepTime()) + ",";
        json += "\"totalTime\": " + std::to_string(recipe.getTotalTime()) + ",";
        json += "\"datePublished\": \"" + recipe.getDatePublished() + "\",";
        json += "\"description\": \"" + recipe.getDescription() + "\",";
        json += "\"category\": \"" + recipe.getCategory() + "\",";
        json += "\"calories\": " + std::to_string(recipe.getCalories()) + ",";
        json += "\"servings\": " + std::to_string(recipe.getServings()) + ",";
        json += "\"yieldQuantity\": " + std::to_string(recipe.getYieldQuantity());
        

        if (json.back() == ',') json.pop_back(); 
        json += " },";
    }
    if (json.back() == ',') json.pop_back();
    json += "]";

    return json;
}



JSValue MyApp::SearchRecipes(const JSObject& thisObject, const JSArgs& args) {
    std::cout << "SearchRecipes called" << std::endl;
    ultralight::String jsStr = args[0].ToString();
    std::string query = std::string(jsStr.utf8().data());

    RecipeDatabase recipeDB;
    std::vector<Recipe> recipes = recipeDB.getRecipesBySearch(query);
    std::string jsonRecipes = convertRecipesToJson(recipes);

    std::cout << "jsonRecipes: " << jsonRecipes.c_str() << std::endl;

    return JSValue(jsonRecipes.c_str());
}

JSValue MyApp::GetMessage(const JSObject& thisObject, const JSArgs& args) {
    std::cout << "GetMessage called" << std::endl;
    ///
    /// Return our message to JavaScript as a JSValue.
    ///
    return JSValue("Hello from C++!<br/>Ultralight rocks!");
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

  ///
  /// Get the global object (this would be the "window" object in JS)
  ///
  JSObject global = JSGlobalObject();

  global["GetMessage"] = BindJSCallbackWithRetval(&MyApp::GetMessage);
  global["SearchRecipes"] = BindJSCallbackWithRetval(&MyApp::SearchRecipes);
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
