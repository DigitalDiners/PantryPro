#ifndef RECIPE_H
#define RECIPE_H

#include <string>

class Recipe {
private:
    int recipeId;
    std::string recipeName;
    int authorId;
    std::string authorName;
    int cookTime, prepTime, totalTime;
    std::string datePublished, description, category;
    int calories, servings, yieldQuantity;

public:
    // Constructor
    Recipe(int id, const std::string& name, int aId, const std::string& aName,
           int cTime, int pTime, int tTime, const std::string& dPublished,
           const std::string& desc, const std::string& cat,
           int cal, int serv, int yieldQ);

    // Getter methods
    int getId() const;
    std::string getName() const;
    int getAuthorId() const;
    std::string getAuthorName() const;
    int getCookTime() const;
    int getPrepTime() const;
    int getTotalTime() const;
    std::string getDatePublished() const;
    std::string getDescription() const;
    std::string getCategory() const;
    int getCalories() const;
    int getServings() const;
    int getYieldQuantity() const;
};

#endif  // RECIPE_H
