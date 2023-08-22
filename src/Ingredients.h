#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <string>
#include <vector>
#include <AppCore/AppCore.h>
#include <map>
#include <memory>

using ultralight::JSObject;
using ultralight::JSArgs;
using ultralight::JSFunction;
using namespace ultralight;

//using namespace std;


class Ingredients {
// public:
//     Ingredients();
//     void getNames() const;
//     void addIngredient(string newIngredient);
//     bool haveIngredient(string newIngredient);
//     void removeIngredient(string removeThis);

// private:
//     vector<string> ingredients;
    virtual void OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) ;

    JSValue addNewIngredient(const JSObject& thisObject, const JSArgs& args);

JSFunction displayIngredients;
JSFunction addIngredient;
JSFunction removeIngredient;
global["GetMessage"] = BindJSCallback(&Ingredients::addNewIngredient);
};

#endif
