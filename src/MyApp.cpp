#include "MyApp.h"
#include "recipe.h"
#include "recipeAPI.h"
#include "recipeDatabase.h"

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 400

MyApp::MyApp() {
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

MyApp::~MyApp() {
}

void MyApp::Run() {
  app_->Run();
}

void MyApp::OnUpdate() {
  ///
  /// This is called repeatedly from the application's update loop.
  ///
  /// You should update any app logic here.
  ///
}

void MyApp::OnClose(ultralight::Window* window) {
  app_->Quit();
}

void MyApp::OnResize(ultralight::Window* window, uint32_t width, uint32_t height) {
  ///
  /// This is called whenever the window changes size (values in pixels).
  ///
  /// We resize our overlay here to take up the entire window.
  ///
  overlay_->Resize(width, height);
}

void MyApp::OnFinishLoading(ultralight::View* caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String& url) {
  ///
  /// This is called when a frame finishes loading on the page.
  ///
}

void MyApp::OnDOMReady(ultralight::View* caller,
                       uint64_t frame_id,
                       bool is_main_frame,
                       const String& url) {
  ///
  /// This is called when a frame's DOM has finished loading on the page.
  ///
  /// This is the best time to setup any JavaScript bindings.
  ///

  auto jsContextLock = caller->LockJSContext(); 
  JSContextRef ctx = jsContextLock->ctx();

    RecipeDatabase db;
    Recipe myRecipe = db.getRecipeById(38);
    RecipeAPI* recipeAPI = new RecipeAPI(&myRecipe);

    JSClassDefinition classDef = kJSClassDefinitionEmpty;
    classDef.className = "RecipeAPI";
    classDef.finalize = [](JSObjectRef obj) {
        RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(obj));
        delete api;
    };

    JSStaticFunction staticFunctions[] = {
        { "getId", &RecipeAPI::getId, kJSPropertyAttributeNone },
        { "getName", &RecipeAPI::getName, kJSPropertyAttributeNone },
        { "getAuthorId", &RecipeAPI::getAuthorId, kJSPropertyAttributeNone },
        { "getCookTime", &RecipeAPI::getCookTime, kJSPropertyAttributeNone },
        { "getPrepTime", &RecipeAPI::getPrepTime, kJSPropertyAttributeNone },
        { "getTotalTime", &RecipeAPI::getTotalTime, kJSPropertyAttributeNone },
        { "getDatePublished", &RecipeAPI::getDatePublished, kJSPropertyAttributeNone },
        { "getDescription", &RecipeAPI::getDescription, kJSPropertyAttributeNone },
        { "getCategory", &RecipeAPI::getCategory, kJSPropertyAttributeNone },
        { "getCalories", &RecipeAPI::getCalories, kJSPropertyAttributeNone },
        { "getServings", &RecipeAPI::getServings, kJSPropertyAttributeNone },
        { "getYieldQuantity", &RecipeAPI::getYieldQuantity, kJSPropertyAttributeNone},
        { NULL, NULL, 0 }
    };

    classDef.staticFunctions = staticFunctions;

    JSClassRef classRef = JSClassCreate(&classDef);
    JSObjectRef obj = JSObjectMake(ctx, classRef, recipeAPI);

    // Set the RecipeAPI object in the global JavaScript context.
    JSStringRef str = JSStringCreateWithUTF8CString("recipeAPI");
    JSObjectSetProperty(ctx, JSContextGetGlobalObject(ctx), str, obj, kJSPropertyAttributeNone, NULL);
    JSStringRelease(str);

}

void MyApp::OnChangeCursor(ultralight::View* caller,
                           Cursor cursor) {
  ///
  /// This is called whenever the page requests to change the cursor.
  ///
  /// We update the main window's cursor here.
  ///
  window_->SetCursor(cursor);
}

void MyApp::OnChangeTitle(ultralight::View* caller,
                          const String& title) {
  ///
  /// This is called whenever the page requests to change the title.
  ///
  /// We update the main window's title here.
  ///
  window_->SetTitle(title.utf8().data());
}


