#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <string>
#include <vector>

using namespace std;


class Ingredients {
public:
    Ingredients();
    void getNames() const;
    void addIngredient(string newIngredient);
    bool haveIngredient(string newIngredient);
    void removeIngredient(string removeThis);

private:
    vector<string> ingredients;
};

#endif
