#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <string>
using namespace std;


class Ingredients {
public:
    Ingredients(const string& name);
    string getName() const;
    void addIngredient() const;

private:
    string name;
};

#endif
