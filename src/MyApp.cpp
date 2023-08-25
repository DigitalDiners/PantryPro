#include "MyApp.h"
#include "recipe.h"
#include "recipeAPI.h"
#include "recipeDatabase.h"

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 400

MyApp::MyApp() {
      // Example of using the RecipeDatabase class to create an instance of a Recipe object 
    // and return its value
	ultralight::Config config;
  ultralight::Settings settings;
  std::cout<<"config and settings";

	// ultralight::Platform::instance().set_config(config);
 
// Get the Platform singleton (maintains global library state)
auto& platform = Platform::instance();
 
  std::cout<<" set platform instance";
// Setup config
Config my_config;
platform.set_config(my_config);
 
// Create platform handlers (these are the minimum required)
// (This is pseudo-code, you will need to define your own)
ultralight::String filePath = BASE_DIRECT;
// MyFileSystem* file_system = new ultralight::GetPlatformFileSystem (&baseDir);
// MyFontLoader* font_loader = new ultralight::GetPlatformFontLoader;

FileSystem* file_system = ultralight::GetPlatformFileSystem(filePath);
  std::cout<<"create file system";

FontLoader* font_loader = ultralight::GetPlatformFontLoader	(		)	;
  std::cout<<"create font loader";

 	
// Setup platform handlers
platform.set_file_system(file_system);
platform.set_font_loader(font_loader);
  std::cout<<"set platform";

 
// Create the Renderer
RefPtr<Renderer> renderer = Renderer::Create();
    //ultralight::RefPtr<ultralight::Renderer> renderer = ultralight::Renderer::Create();
    
  std::cout<<"create renderer";

    const ultralight::ViewConfig viewFig;

    ultralight::RefPtr<ultralight::View> view = renderer->CreateView(800, 600, viewFig, nullptr);
  std::cout<<"create view";


// ul::RefPtr<ul::View> newView;
// 	newView = renderer->CreateView(800, 600, false, nullptr);

    RecipeDatabase db;
    Recipe recipe = db.getRecipeById(38);

  RecipeAPI* recipeApi = new RecipeAPI(&recipe); // Instantiate your C++ class
  std::cout<<"instantiate c++ class";

// overlay->view()->SetJSContextGlobalObject("RecipeAPI", &recipeApi); // Expose the C++ object to JavaScript
// overlay->view()->LoadURL("your_html_file.html");
  ///
  /// Create our main App instance.
  ///
  app_ = App::Create();
  std::cout<<"create app";

  ///
  /// Create a resizable window by passing by OR'ing our window flags with
  /// kWindowFlags_Resizable.
  ///
  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
    false, kWindowFlags_Titled | kWindowFlags_Resizable);
  std::cout<<"create window";

  ///
  /// Create our HTML overlay-- we don't care about its initial size and
  /// position because it'll be calculated when we call OnResize() below.
  ///
  //overlay_ = Overlay::Create(window_, 1, 1, 0, 0);
ultralight::RefPtr<ultralight::Overlay> overlay = ultralight::Overlay::Create(window_, view, 0, 0);
  std::cout<<"create overlay";

  ///
  /// Force a call to OnResize to perform size/layout of our overlay.
  ///
  OnResize(window_.get(), window_->width(), window_->height());

  ///
  /// Load a page into our overlay's View
  ///
  overlay_->view()->LoadURL("file:///app.html");
  std::cout<<"load url";

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


