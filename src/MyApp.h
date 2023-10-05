#pragma once
#include <AppCore/AppCore.h>
#include <JavaScriptCore/JSBase.h>
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSStringRef.h>
#include <JavaScriptCore/JSObjectRef.h>
#include <JavaScriptCore/JSValueRef.h>

#include "recipeDatabase.h"


using namespace ultralight;

class MyApp : public AppListener,
              public WindowListener,
              public LoadListener,
              public ViewListener
{
public:
  MyApp();

  virtual ~MyApp();

  // Start the run loop.
  virtual void Run();

  // This is called continuously from the app's main loop.
  virtual void OnUpdate() override;

  // This is called when the window is closing.
  virtual void OnClose(ultralight::Window *window) override;

  // This is called whenever the window resizes.
  virtual void OnResize(ultralight::Window *window, uint32_t width, uint32_t height) override;

  // This is called when the page finishes a load in one of its frames.
  virtual void OnFinishLoading(ultralight::View *caller,
                               uint64_t frame_id,
                               bool is_main_frame,
                               const String &url) override;

  std::string removeQuotes(const std::string& input);


  JSValue SearchRecipes(const JSObject& thisObject, const JSArgs& args);

  /**
   * @brief Retrieve the planner json file from the MealPlanner object
   * 
   * @param thisObject self.
   * @param args args to be passed, function uses none.
   * @return JSString the planner json as a stdstring.
   */
  JSValue GetPlanner(const JSObject& thisObject, const JSArgs& args);

  void SaveOnExit();

  JSValue GetIngredientsByRecipe(const JSObject& thisObject, const JSArgs& args);

  JSValue GetReviewsByRecipe(const JSObject& thisObject, const JSArgs& args);

  // JSValue RecipeIngredients(const JSObject& thisObject, const JSArgs& args);

JSValue AddToMealPlanner(const JSObject& thisObject, const JSArgs& args);

JSValue GetSaved(const JSObject& thisObject, const JSArgs& args);

void UnsaveRecipe(const JSObject& thisObject, const JSArgs& args);

JSValue ShowFeatured(const JSObject& thisObject, const JSArgs& args);

void SaveRecipe(const JSObject& thisObject, const JSArgs& args);

  std::string convertRecipesToJson(const std::vector<Recipe>& recipes);

  // This is called when the DOM has loaded in one of its frames.
  virtual void OnDOMReady(ultralight::View *caller,
                          uint64_t frame_id,
                          bool is_main_frame,
                          const String &url) override;

  // This is called when the page requests to change the Cursor.
  virtual void OnChangeCursor(ultralight::View *caller,
                              Cursor cursor) override;

  virtual void OnChangeTitle(ultralight::View *caller,
                             const String &title) override;

protected:
  RefPtr<App> app_;
  RefPtr<Window> window_;
  RefPtr<Overlay> overlay_;
};
