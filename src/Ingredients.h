#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <string>
#include <vector>
#include <AppCore/AppCore.h>
#include <map>
#include <memory>
#include <iostream>
#include <stdio.h>

using namespace std;



using ultralight::JSObject;
using ultralight::JSArgs;
using ultralight::JSFunction;
using namespace ultralight;


class Ingredients {
 public:
    virtual ~Ingredients() {};
//     void getNames() const;
//     void addIngredient(string newIngredient);
//     bool haveIngredient(string newIngredient);
//     void removeIngredient(string removeThis);
    //void AddNewIngredient(string newIngredient);
    vector<string> ingredients;
    JSValue AddNewIngredient(const JSObject& thisObject, const JSArgs& args);
    void prep();
    virtual void OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) ;
 private:


JSFunction displayIngredients;
JSFunction addIngredient;
JSFunction removeIngredient;
//global["GetMessage"] = BindJSCallback(&Ingredients::addNewIngredient);
};


#endif
