#include "Ingredients.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>


//Link with JS here with the JS functions.
//JS functions wanted include: 
//Add ingredient
//Remove ingredient
//Display ingredients
void Ingredients::OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) {
JSObject global = JSGlobalObject();
displayIngredients = global["displayIngredients"];
addIngredient = global["addIngredient"];
removeIngredient = global["removeIngredient"];
global["GetMessage"] = BindJSCallback(&Ingredients::addNewIngredient);

}

JSValue addNewIngredient(String newIngredient){
    //RefPtr<JSContext> lock(view() -> LockJSContext());
    addIngredient(String newIngredient);
}
//JSValue newIngredient

//using namespace std;

// vector<string> ingredientStore;

// Ingredients::Ingredients() {}

// void Ingredients::getNames() const {
//     if (ingredients.size()==0){
//         cout << "There are no ingredients listed\n";
//     }else{
//         cout<<" Here is the list of ingredients you have\n";
//         for(const string ingredient : ingredientStore){
//             cout << "- "<<ingredient<<"\n";
//         }
//     }
// }

// void Ingredients::addIngredient(string newIngredient) {
//     ingredientStore.push_back(newIngredient);
// }

// void Ingredients::removeIngredient(string removeThis){
//     if(ingredientStore.size()==0){
//         cout<<"There are no ingredients to remove\n";
//         return;
//     }
//     if(haveIngredient(removeThis)){
//         auto it = find(ingredientStore.begin(), ingredientStore.end(), removeThis);

//         cout<<&it;
//         if(it!=ingredientStore.end()){//old ingredient found in vector
//         ingredientStore.erase(it); //delete ingredient via index
//         cout<< removeThis<<" has been removed\n";
//         return;
//         }
//     }
//     cout<< removeThis<<" is not on the list\n";
// }

// bool Ingredients::haveIngredient(string newIngredient) {
//     char* new_array = new char[newIngredient.length() +1];
//     new_array[newIngredient.length()] = '\0';
//     for(int i=0; i<newIngredient.length(); i++){
//         new_array[i] = newIngredient[i];
//     }
//     for( string ingredient : ingredients){
//         char* old_array = new char[ingredient.length() +1];
//         old_array[ingredient.length()] = '\0';
//         cout<<"checking "<<ingredient;
//         for(int i=0; i<ingredient.length(); i++){
//             old_array[i] = ingredient[i];
//         }
//         if(strcmp(new_array, old_array)){
//             cout<<"have ingredient\n";
//             delete[] new_array;
//             delete[] old_array;
//             return true;
//         }
//         delete[] old_array;
//     }
//     delete[] new_array;
//     return false;
// }

