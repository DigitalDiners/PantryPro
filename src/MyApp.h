#pragma once
#include <string>
#include "recipe.h"
#include "recipeAPI.h"
#include "recipeDatabase.h"

#include <AppCore/AppCore.h>
#include <JavaScriptCore/JSBase.h>
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSStringRef.h>
#include <JavaScriptCore/JSObjectRef.h>
#include <JavaScriptCore/JSValueRef.h>
#include "recipeAPI.h"
#include <Ultralight/Ultralight.h>
#include <Ultralight/platform/Config.h>
#include <Ultralight/platform/Platform.h>
#include <Ultralight/Renderer.h>
#include <Ultralight/View.h>
#include <Ultralight/String.h> // Include this for Ultralight String type


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
