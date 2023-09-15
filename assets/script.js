let ingredients = [];
let currRecipeName;
let savedRecipes = [];
let mealPlanner = [];


function addIngredient() {
    const ingredientInput = document.getElementById('ingredient-input');
    const ingredientList = document.getElementById('ingredient-list');

    const listItem = document.createElement('li');
    listItem.textContent = ingredientInput.value;

    const removeButton = document.createElement('button');
    removeButton.textContent = 'Remove';
    removeButton.onclick = function() {
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

    console.log("Ingredients:", ingredients);

    try {

        // debugging instructions if search recipes does not return results
        
        // 1. uncomment the lines below, re-build and re-run application
        //var message = SearchRecipes(ingredientStr);
        //document.getElementById('message').innerHTML = message;

        // 2. copy and paste json into following link:
        // https://jsonlint.com

        // 3. if json is invalid, find recipe causing issue

        const jsonRecipes = SearchRecipes(ingredients);
        const recipes = JSON.parse(jsonRecipes);
        console.log("Recipes:", recipes);

        for (let recipe of recipes) {
            displayCard(recipe);
        }
    } catch (error) {
        console.error("Error fetching recipes:", error);
        alert("Failed to fetch recipes. Please try again later.");
    }
}

function createStars(rating) {
    const starsWrapper = document.createElement('div');
    for (let i = 1; i <= 5; i++) {
      const star = document.createElement('span');
      star.className = 'star';
      star.textContent = '★';
      if (i <= rating) {
        star.classList.add('checked');
      }
      starsWrapper.appendChild(star);
    }
    return starsWrapper;
  }
  
function displayCard(recipe) {
    const searchResults = document.getElementById('search-results');

    const card = document.createElement('div');
    card.className = 'recipe-card';

    const recipeInfo = document.createElement('div');
    recipeInfo.className = 'recipe-info';

    const name = document.createElement('div');
    name.className = 'recipe-name';
    name.textContent = recipe.recipeName;
    recipeInfo.appendChild(name);

    if (recipe.recipeImageURL) { // Check if image URL exists
        const imageWrapper = document.createElement('div'); // Create a wrapper for image
        imageWrapper.className = 'recipe-image';

        const image = document.createElement('img');
        image.src = recipe.recipeImageURL;

        imageWrapper.appendChild(image); // append img to its wrapper
        card.appendChild(imageWrapper); // append the wrapper to the card
    }

    const category = document.createElement('div');
    category.className = 'recipe-category';
    category.textContent = recipe.category;
    recipeInfo.appendChild(category);

    const favourite = document.createElement("div");
    favourite.className = ("favourite-icon");
    favourite.textContent = "♡";
    favourite.onclick = function(){
    addToSaved(recipe.recipeName);};

  
    const addSymbol = document.createElement("div");
    addSymbol.className = ("add-symbol");
    addSymbol.textContent = "+";
    addSymbol.onclick = function(){
    openPopup(recipe.recipeName);};
  
    const popupContainer = document.createElement("div");
    popupContainer.id = "popup";
    popupContainer.className = ("popup-container");
  
    const popupDiv = document.createElement("div");
    popupDiv.className = ("popup");
  
    // Create a <span> element with class "close-popup" and text "×"
    const spanClosePopup = document.createElement("span");
    spanClosePopup.className = ("close-popup");
    spanClosePopup.textContent = "×";
    spanClosePopup.onclick = function(){
    (closePopup());};
  
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
    buttonAddMeal.onclick = function(){
    (addToPlanner(recipe.recipeName));};
    // buttonAddMeal.addEventListener("click", function () {
    //   addToPlanner(recipe.recipeName); // You can replace this with your desired meal ID
    // });
  
    // Append elements to create the desired structure
    popupDiv.appendChild(spanClosePopup);
    popupDiv.appendChild(h2);
    popupDiv.appendChild(selectDayOptions);
    popupDiv.appendChild(selectMealOptions);
    popupDiv.appendChild(buttonAddMeal);
  
    popupContainer.appendChild(popupDiv);
  
    recipeInfo.appendChild(favourite);
    recipeInfo.appendChild(addSymbol);
    recipeInfo.appendChild(popupContainer);
  

    const calories = document.createElement('div');
    calories.className = 'recipe-calories';
    calories.textContent = recipe.calories + ' Calories';
    recipeInfo.appendChild(calories);

    const rating = document.createElement('div');
    rating.className = 'recipe-rating';
    const starsWrapper = createStars(recipe.rating);
    rating.appendChild(starsWrapper);
    recipeInfo.appendChild(rating);

    card.appendChild(recipeInfo);

    searchResults.appendChild(card);
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
  
  function addToJSON(day, meal, recipeName){
      //assets/css/data/planner.json
      if (weeklyMealPlan[day] && weeklyMealPlan[day][meal] !== undefined) {
          if(weeklyMealPlan[day][meal]==null){        
              weeklyMealPlan[day][meal] = recipeName;
              console.log("Recipe: " + recipeName + " added to planner on " + day + " for " + meal +  "!");
              const jsonstring = JSON.stringify(weeklyMealPlan);
              if(AddToMealPlanner(jsonstring)){
                  console.log("success");
              }else{
                  console.log("fail");
              }
          }else{
              console.log("This slot is already filled");
          }
      } else {
          console.log("Invalid day or meal type");
        }
  }
      
  
  function addToSaved(recipeID) {
      // Communicate with C++ method to save the recipe
      console.log("Recipe with ID " + recipeID + " saved!");
      savedRecipes.push(recipeID);
      console.log("saved recipe(s):\n")
      for(let i=0; i<savedRecipes.length; i++){
          console.log(savedRecipes[i]+"\n");
      }
  }
  
  /**
   * add to planner function
   * opening a popup sets the currRecipeId to the clicked recipe. 
   * Need to add function to add the recipe, day, and meal to an array or script
   */
  function addToPlanner(recipeName) {
      recipeName = currRecipeName;
      const dayOptions = document.getElementById('day-options');
      const mealOptions = document.getElementById('meal-options');
      const selectedDay = dayOptions.value;
      const selectedMeal = mealOptions.value;
      let mealOption = [];
      addToJSON(selectedDay, selectedMeal, recipeName);
      mealOption.push(selectedDay, selectedMeal, recipeName);
      mealPlanner.push(mealOption);
      closePopup();
  }
  
  // Function to open the popup
  function openPopup(recipeName) {
      currRecipeName = recipeName;
      const popup = document.getElementById("popup");
      popup.style.display = 'block';
  }
  
  // Function to close the popup
  function closePopup() {
    const popup = document.getElementById("popup");
    popup.style.display = 'none';
  }
  
  