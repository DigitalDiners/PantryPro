let ingredients = [];
let currRecipeId;
let savedRecipes = [];
let mealPlanner = [];
let currSaved = [];
let currSavedNames = [];



function addIngredient() {
    const ingredientInput = document.getElementById('ingredient-input');
    const ingredientList = document.getElementById('ingredient-list');

    const listItem = document.createElement('li');
    listItem.textContent = ingredientInput.value;

    const removeButton = document.createElement('button');
    removeButton.textContent = 'Remove';
    removeButton.onclick = function () {
        ingredientList.removeChild(listItem);
    };
    listItem.appendChild(removeButton);

    ingredientList.appendChild(listItem);

    ingredientInput.value = '';
}

function searchRecipes() {

    const searchResults = document.getElementById('search-results');
    searchResults.innerHTML = '';

    const ingredientList = document.getElementById('ingredient-list');
    const ingredients = [];

    for (let i = 0; i < ingredientList.children.length; i++) {
        ingredients.push(ingredientList.children[i].textContent.replace('Remove', '').trim());
    }

    // currSaved = GetSaved();
    // if (!currSaved.size() == 0) {
    //     currSaved.forEach((saved) => currSavedNames.push(saved.recipeId));
    // } 

    // uncomment to view a json of reviews for a given recipe (also comment out try catch block below)
    // var reviews = GetReviewsByRecipe(524);
    // document.getElementById('search-results').innerHTML = reviews;


    try {

        // debugging instructions if search recipes does not return results

        // 1. uncomment the lines below, re-build and re-run application
        //var message = SearchRecipes(ingredientStr);
        //document.getElementById('search-results').innerHTML = message;

        // 2. copy and paste json into following link:
        // https://jsonlint.com

        // 3. if json is invalid, find recipe causing issue

        const jsonRecipes = SearchRecipes(ingredients);
        const recipes = JSON.parse(jsonRecipes);

        const recipeIds = recipes.map(r => r.recipeId);
        // Fetch ingredients for all these recipes
        const jsonIngredients = GetIngredientsForRecipes(recipeIds);
        const allIngredients = JSON.parse(jsonIngredients);

        console.log("Recipes:", recipes);
        document.getElementById('search-results').innerHTML = "";

        document.getElementById('search-results').innerHTML = "";
        for (let recipe of recipes) {
            const recipeIngredients = allIngredients[recipe.recipeId];
            displayCard(recipe, "search-results", recipeIngredients);
        }
    } catch (error) {
        console.error("Error fetching recipes:", error);
        alert("Failed to fetch recipes. Please try again later.");
    }
}

/** Create the star rating for the recipecard */
function createStars(rating) {
    const starsWrapper = document.createElement("div");
    for (let i = 1; i <= 5; i++) {
        const star = document.createElement("span");
        star.className = "star";
        star.textContent = "★";
        if (i <= rating) {
            star.classList.add('checked');
        }
        starsWrapper.appendChild(star);
    }
    return starsWrapper;
}

/*
var msnry;
// Wait for the content to load
document.addEventListener('DOMContentLoaded', function () {
    // Initialize masonry
    var grid = document.querySelector('#search-results');
    msnry = new Masonry(grid, {
        // options
        itemSelector: '.recipe-card',
        columnWidth: '.recipe-card',
        percentPosition: true
    });
});
*/

function displayCard(recipe, location, ingredientsArray) {
    const searchResults = document.getElementById(location);


    let recipeName = recipe.recipeName;
    if (recipeName.length > 18) {
        recipeName = recipeName.substring(0, 17);
        recipeName += "...";
    }

    // Create a div for the card
    const card = document.createElement('div');
    card.className = 'recipe-card';

    // Create a div for recipe info
    const recipeInfo = document.createElement('div');
    recipeInfo.className = 'recipe-info';

    // Add name to the card
    const name = document.createElement('h2');
    name.className = 'recipe-name';
    name.textContent = recipe.recipeName;
    recipeInfo.appendChild(name);

    // Add image if it exists to the card
    if (recipe.recipeImageURL) { // Check if image URL exists
        const imageWrapper = document.createElement('div'); // Create a wrapper for image
        imageWrapper.className = 'recipe-image';

        const image = document.createElement('img');
        image.src = recipe.recipeImageURL;

        imageWrapper.appendChild(image); // append img to its wrapper
        card.appendChild(imageWrapper); // append the wrapper to the card
    }

    // Add category to the card
    const category = document.createElement('div');
    category.className = 'recipe-category';
    category.textContent = recipe.category;
    recipeInfo.appendChild(category);

    // Add calories to the card
    const calories = document.createElement('div');
    calories.className = 'recipe-calories';
    calories.textContent = recipe.recipeCalories + ' Calories';
    recipeInfo.appendChild(calories);

    // Add rating to the card
    const rating = document.createElement('div');
    rating.className = 'recipe-rating';
    const starsWrapper = createStars(recipe.firstRating);
    rating.appendChild(starsWrapper);
    recipeInfo.appendChild(rating);

    // Add ingredients to the card
    const ingredientsDiv = document.createElement('div');
    ingredientsDiv.className = 'recipe-ingredients';
    const ingredientsHeader = document.createElement('h3');
    ingredientsHeader.textContent = 'Ingredients';
    ingredientsDiv.appendChild(ingredientsHeader);
    const ingredientsList = document.createElement('ul');
    for (const ingredient of ingredientsArray) {
        const ingredientItem = document.createElement('li');
        ingredientItem.textContent = ingredient.Name;
        ingredientsList.appendChild(ingredientItem);
    }
    ingredientsDiv.appendChild(ingredientsList);
    recipeInfo.appendChild(ingredientsDiv);

    // Add instructions to the card
    if (recipe.instructions && recipe.instructions.trim() !== '') {
        const instructionsDiv = document.createElement('div');
        instructionsDiv.className = 'recipe-instructions';
        const instructionsHeader = document.createElement('h3');
        instructionsHeader.textContent = 'Instructions';
        instructionsDiv.appendChild(instructionsHeader);
        const instructionList = document.createElement('ol');
        const instructionArray = recipe.instructions.split('|');
        for (const instruction of instructionArray) {
            const instructionItem = document.createElement('li');
            instructionItem.textContent = instruction.trim();
            instructionList.appendChild(instructionItem);
        }
        instructionsDiv.appendChild(instructionList);
        recipeInfo.appendChild(instructionsDiv);
    }

    // Add favorite button to the card
        const favourite = document.createElement("button");
        favourite.className = ("favourite-icon");
        favourite.innerHTML = "&hearts;";
        favourite.setAttribute("aria-label", "Add to favourites");
        favourite.onclick = function () {
            addToSaved(recipe.recipeId);
        };
        const unsave = document.createElement("button");
        unsave.className = ("unsave-icon");
        unsave.innerHTML = "&times;";
        unsave.setAttribute("aria-label", "Remove from Favourites");
        unsave.onclick = function () {
            unSave(recipe.recipeId);
        };

    // // Add 'add to planner' button to the card
    const addSymbol = document.createElement("button");
    addSymbol.className = ("add-symbol");
    addSymbol.innerHTML = "Add to planner";
    addSymbol.setAttribute("aria-label", "Add to planner");
    addSymbol.onclick = function () {
        openPopup(recipe.recipeId);
    };

    const popupContainer = document.createElement("div");
    popupContainer.id = "popup";
    popupContainer.className = ("popup-container");

    const popupDiv = document.createElement("div");
    popupDiv.className = ("popup");

    // Create a <span> element with class "close-popup" and text "×"
    const spanClosePopup = document.createElement("span");
    spanClosePopup.className = ("close-popup");
    spanClosePopup.textContent = "×";
    spanClosePopup.onclick = function () {
        (closePopup());
    };

    // Create an <h2> element with text "Select Meals"
    const h2 = document.createElement("h2");
    h2.textContent = "Select Meal";

    // Create a <select> element with id "day-options" and options
    const selectDayOptions = document.createElement("select");
    selectDayOptions.id = "day-options";
    const days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"];
    for (const day of days) {
        const option = document.createElement("option");
        option.value = day;
        option.textContent = day;
        selectDayOptions.appendChild(option);
    }

    // Create a <select> element with id "meal-options" and options
    const selectMealOptions = document.createElement("select");
    selectMealOptions.id = "meal-options";
    const meals = ["Breakfast", "Lunch", "Dinner"];
    for (const meal of meals) {
        const option = document.createElement("option");
        option.value = meal;
        option.textContent = meal;
        selectMealOptions.appendChild(option);
    }

    // Create a <button> element with id "add-meal" and text "Add Meal"
    const buttonAddMeal = document.createElement("button");
    buttonAddMeal.id = "add-meal";
    buttonAddMeal.textContent = "Add Meal";
    buttonAddMeal.onclick = function () {
        (addToPlanner(recipe.recipeName, recipe.recipeId));
    };

    // Append elements to create the desired structure
    popupDiv.appendChild(spanClosePopup);
    popupDiv.appendChild(h2);
    popupDiv.appendChild(selectDayOptions);
    popupDiv.appendChild(selectMealOptions);
    popupDiv.appendChild(buttonAddMeal);

    popupContainer.appendChild(popupDiv);
    
    recipeInfo.appendChild(favourite);
    recipeInfo.appendChild(unsave);
    recipeInfo.appendChild(addSymbol);
    recipeInfo.appendChild(popupContainer);

    card.appendChild(recipeInfo);
    searchResults.appendChild(card);

    //if (msnry) {
    //    msnry.appended(card);
    //    msnry.layout();
    //}
    
}

function showToast(message) {
    const toast = document.getElementById('toast');
    toast.textContent = message;
    toast.style.opacity = "1";
    setTimeout(function () {
        toast.style.opacity = "0";
    }, 3000);
}

//send to c the recipeId
function addToSaved(recipeId) {
    // Communicate with C++ method to save the recipe
    console.log("Recipe " + recipeId + " saved!");
    let isSaved = false;

    for (let i = 0; i < savedRecipes.length; i++) {
        if (savedRecipes[i] == recipeId) {
            isSaved = true;
        }
    }
    if (!isSaved) {
        savedRecipes.push(recipeId);
        console.log("saved recipe(s):\n")
        SaveRecipe(recipeId);
        showToast('Recipe saved successfully!'); 

    } else {
        console.log("already saved\n")
        showToast('Recipe already saved!');  
    }
}

function unSave(recipeId) {
    const index = savedRecipes.indexOf(recipeId);
    
    if (index > -1) {
        savedRecipes.splice(index, 1);
        UnsaveRecipe(recipeId); 
        showToast('Recipe removed from favorites!'); 
    } else {
        console.log("Recipe not in saved list\n");
        showToast('Recipe not in favorites!');
    }
}

//function which retrieves saved recipes from c
function getSaved() {
    try {
        const jsonRecipes = GetSaved();
        const recipes = JSON.parse(jsonRecipes);

        const recipeIds = recipes.map(r => r.recipeId);
        // Fetch ingredients for all these recipes
        const jsonIngredients = GetIngredientsForRecipes(recipeIds);
        const allIngredients = JSON.parse(jsonIngredients);

        console.log("Recipes:", recipes);
        document.getElementById('saved-recipe-container').innerHTML = "";

        // currSaved = GetSaved();
        // currSaved.forEach((saved) => currSavedNames.push(saved.recipeId));

        for (let recipe of recipes) {
            const recipeIngredients = allIngredients[recipe.recipeId];
            displayCard(recipe, 'saved-recipe-container', recipeIngredients);
        }
    } catch (error) {
        console.error("Error fetching recipes:", error);
        alert("Failed to fetch recipes. Please try again later.");
    }
}

function getAndrews() {
    try {
        const jsonRecipes = GetAndrews();
        const recipes = JSON.parse(jsonRecipes);

        const recipeIds = recipes.map(r => r.recipeId);
        // Fetch ingredients for all these recipes
        const jsonIngredients = GetIngredientsForRecipes(recipeIds);
        const allIngredients = JSON.parse(jsonIngredients);

        console.log("Recipes:", recipes);
        document.getElementById('andrews-recipe-container').innerHTML = "";

        for (let recipe of recipes) {
            const recipeIngredients = allIngredients[recipe.recipeId];
            displayCard(recipe, 'andrews-recipe-container', recipeIngredients);
        }
    } catch (error) {
        console.error("Error fetching recipes:", error);
        alert("Failed to fetch recipes. Please try again later.");
    }
}


function getFeatured() {
    try {
        const jsonRecipes = ShowFeatured();
        const recipes = JSON.parse(jsonRecipes);

        const recipeIds = recipes.map(r => r.recipeId);
        // Fetch ingredients for all these recipes
        const jsonIngredients = GetIngredientsForRecipes(recipeIds);
        const allIngredients = JSON.parse(jsonIngredients);

        console.log("Recipes:", recipes);
        document.getElementById('featured-recipe-container').innerHTML = "";

        for (let recipe of recipes) {
            const recipeIngredients = allIngredients[recipe.recipeId];
            displayCard(recipe, 'featured-recipe-container', recipeIngredients);
        }
    } catch (error) {
        console.error("Error fetching recipes:", error);
        alert("Failed to fetch recipes. Please try again later.");
    }
}

function loadSavedPage() {
    document.getElementById('saved-recipe-container').innerHTML = "";

    for (let i = 0; i < savedRecipes.length(); i++) {
        displayCard(savedRecipes[i], 'saved-recipe-container');
    }
}

/**
 * add to planner function
 * opening a popup sets the currRecipeId to the clicked recipe. 
 * Need to add function to add the recipe, day, and meal to an array or script
 */
function addToPlanner(recipeName, recipeId) {
    const dayOptions = document.getElementById('day-options');
    const mealOptions = document.getElementById('meal-options');
    const selectedDay = dayOptions.value;
    const selectedMeal = mealOptions.value;
    let mealOption = [];
    addToJSON(selectedDay, selectedMeal, recipeName, currRecipeId);
    mealOption.push(recipeName, currRecipeId, selectedDay, selectedMeal);
    mealPlanner.push(mealOption);
    closePopup();
}

// Your JSON structure
const weeklyMealPlan = {
    "Monday": {
        "Breakfast": null,
        "Lunch": null,
        "Dinner": null,
        "Snack": null
    },
    "Tuesday": {
        "Breakfast": null,
        "Lunch": null,
        "Dinner": null,
        "Snack": null
    },
    "Wednesday": {
        "Breakfast": null,
        "Lunch": null,
        "Dinner": null,
        "Snack": null
    },
    "Thursday": {
        "Breakfast": null,
        "Lunch": null,
        "Dinner": null,
        "Snack": null
    },
    "Friday": {
        "Breakfast": null,
        "Lunch": null,
        "Dinner": null,
        "Snack": null
    },
    "Saturday": {
        "Breakfast": null,
        "Lunch": null,
        "Dinner": null,
        "Snack": null
    },
    "Sunday": {
        "Breakfast": null,
        "Lunch": null,
        "Dinner": null,
        "Snack": null
    }
};

function addToJSON(day, meal, recipeName, recipeId) {
    if (weeklyMealPlan[day] && weeklyMealPlan[day][meal] !== undefined) {
        if (weeklyMealPlan[day][meal] == null) {
            weeklyMealPlan[day][meal] = recipeName;
            console.log("Recipe: " + recipeName + " added to planner on " + day + " for " + meal + "!");
            let done = AddToMealPlanner(recipeName, currRecipeId, day, meal);
            if (done) {
                console.log("success");
            } else {
                console.log("fail");
            }
        } else {
            console.log("This slot is already filled");
            // filledPopup(); - this will create a popup for abt 2 seconds maybe?
        }
    } else {
        console.log("Invalid day or meal type");
    }
}

// Function to open the popup
function openPopup(recipeId) {
    currRecipeId = recipeId;
    const popup = document.getElementById("popup");
    popup.style.display = 'block';
}

// Function to close the popup
function closePopup() {
    const popup = document.getElementById("popup");
    popup.style.display = 'none';
}

function toggleRecipes(button, type) {
    if (button.innerHTML === 'Show') {
        button.innerHTML = 'Hide';
        switch (type) {
            case 'andrews':
                getAndrews();
                break;
            case 'saved':
                getSaved();
                break;
            case 'featured':
                getFeatured();
                break;
        }
    } else {
        button.innerHTML = 'Show';
        hideRecipes(type);
    }
}

function hideRecipes(type) {
    switch (type) {
        case 'andrews':
            document.getElementById('andrews-recipe-container').innerHTML = '';
            break;
        case 'saved':
            document.getElementById('saved-recipe-container').innerHTML = '';
            break;
        case 'featured':
            document.getElementById('featured-recipe-container').innerHTML = '';
            break;
    }
}

