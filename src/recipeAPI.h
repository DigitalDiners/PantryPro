//#pragma once
#include <Ultralight/Ultralight.h>
#include "recipe.h"

class RecipeAPI {
public:
    // Bind our static functions to JS for the given view.
    static void BindToJS(ultralight::View* view);

    // Static functions to bind.
    static ultralight::JSValue GetId(const ultralight::JSObject& obj, const ultralight::JSArgs& args);
    static ultralight::JSValue GetName(const ultralight::JSObject& obj, const ultralight::JSArgs& args);
    static ultralight::JSValue GetAuthorId(const ultralight::JSObject& obj, const ultralight::JSArgs& args);
    static ultralight::JSValue GetCookTime(const ultralight::JSObject& obj, const ultralight::JSArgs& args);
};
