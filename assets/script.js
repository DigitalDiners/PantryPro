let ingredients = [];
let currRecipeName;
let savedRecipes = [];
let mealPlanner = [];

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
    popup.style.display = 'block';
}

// Function to close the popup
function closePopup() {
    popup.style.display = 'none';
}


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

    //console.log("Recipe Name:", recipe.recipeName);

    //const name = document.createElement('div');
    //name.className = 'recipe-name';
    //name.textContent = recipe.recipeName;
    //card.appendChild(name);

    //const image = document.createElement('img');
    //image.className = 'recipe-image';
    //image.src = recipe.recipeImageURL;
    //card.appendChild(image);

    const recipeInfo = document.createElement('div');
    recipeInfo.className = 'recipe-info';

    const name = document.createElement('div');
    name.className = 'recipe-name';
    name.textContent = 'recipe name';
    recipeInfo.appendChild(name);

    // if (recipe.recipeImageURL) { // Check if image URL exists
    //     const imageWrapper = document.createElement('div'); // Create a wrapper for image
    //     imageWrapper.className = 'recipe-image';

    //     const image = document.createElement('img');
    //     image.src = recipe.recipeImageURL;

    //     imageWrapper.appendChild(image); // append img to its wrapper
    //     card.appendChild(imageWrapper); // append the wrapper to the card
    // }

    const category = document.createElement('div');
    category.className = 'recipe-category';
    category.textContent = 'recipe.category';
    recipeInfo.appendChild(category);

    const calories = document.createElement('div');
    calories.className = 'recipe-calories';
    calories.textContent = 'recipe.calories' + ' Calories';
    recipeInfo.appendChild(calories);

    const rating = document.createElement('div');
    rating.className = 'recipe-rating';
    const starsWrapper = createStars(3);
    rating.appendChild(starsWrapper);
    recipeInfo.appendChild(rating);

    card.appendChild(recipeInfo);


    // const saveButton = document.createElement('button');
    // saveButton.textContent = 'Save';
    // saveButton.onclick = function() {
    //     addToSaved(recipe.recipeId);
    // };
    // card.appendChild(saveButton);

    // const addToPlannerButton = document.createElement('button');
    // addToPlannerButton.textContent = 'Add to Planner';
    // addToPlannerButton.onclick = function() {
    //     addToPlanner(recipe.recipeId, 'Monday');
    // };
    // card.appendChild(addToPlannerButton);
    
    // Create and set the recipeInfo display
    searchResults.appendChild(card);
}
displayCard()

// add_button = document.getElementById("add-button");
// document.getElementById("ingredient-input").addEventListener('keydown', function(event) {
//     if (event.keyCode === 13) {
//         event.preventDefault();
//         add_button.click();
//     }
// });


// function displayIngredients() {
//     const listElem = document.getElementById("ingredient-list");
//     listElem.innerHTML = "";
    
//     for (let ingredient of ingredients) {
//         let li = document.createElement('li');
//         li.textContent = ingredient;

//         let deleteButton = document.createElement('button');
//         deleteButton.textContent =  "\u2715";
//         deleteButton.onclick = function() {
//             removeIngredient(ingredient);
//         };
//         li.appendChild(deleteButton);

//         listElem.appendChild(li);
//     }
// }

// function removeIngredient(ingredient) {
//     const index = ingredients.indexOf(ingredient);
//     if (index > -1) {
//         ingredients.splice(index, 1);
//         displayIngredients();
//     }
// }


// function getRecipeInfo(recipeID) {
//     // This would communicate with your C++ method to get recipe information
//     // Example return, adjust as needed:
//     return {
//         recipeName: "Sample Recipe Name",
//         RecipeInfo: "RecipeName",
//     };
// }

// function addToSaved(recipeID) {
//     // Communicate with your C++ method to save the recipe
//     console.log("Recipe with ID " + recipeID + " saved!");
// }

// function addToPlanner(recipeID, day) {
//     // Communicate with your C++ method to add the recipe to the planner on the given day
//     console.log("Recipe with ID " + recipeID + " added to planner for " + day + "!");
// }

// // Sample call to display a card (replace with actual method to get results from backend)
// const sampleRecipe = getRecipeInfo(1);
// displayCard(sampleRecipe);

// /* GPTD */
// function exportTableToCSV(filename) {
//     var csv = [];
//     var rows = document.querySelectorAll(".meal-planner tr");
    
//     for (var i = 0; i < rows.length; i++) {
//         var row = [], cols = rows[i].querySelectorAll("td, th");
        
//         for (var j = 0; j < cols.length; j++) {
//             // To handle commas in the content and multiline data:
//             var cellContent = cols[j].innerText.replace(/"/g, '""');
//             cellContent = '"' + cellContent + '"';
//             row.push(cellContent);
//         }
        
//         csv.push(row.join(","));        
//     }

//     // Create CSV file and download
//     var csvFile = new Blob([csv.join("\n")], { type: "text/csv" });
//     var downloadLink = document.createElement("a");
//     downloadLink.download = filename;
//     downloadLink.href = window.URL.createObjectURL(csvFile);
//     downloadLink.style.display = "none";
//     document.body.appendChild(downloadLink);
//     downloadLink.click();
// }
