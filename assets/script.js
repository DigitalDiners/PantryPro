let ingredients = [];
let currRecipeId;
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
        let jsonIngredients = [];

        for (let recipe of recipes) {
            displayCard(recipe);
            jsonIngredients.push(RecipeIngredients(recipe));
        }
    } catch (error) {
        console.error("Error fetching recipes:", error);
        alert("Failed to fetch recipes. Please try again later.");
    }
}


function displayCard(recipe) {
    const searchResults = document.getElementById('search-results');

    const card = document.createElement('div');
    card.className = 'recipe-card';

    //doccument.createElement('img');
    console.log("Recipe Name:", recipe.recipeName);

    const name = document.createElement('div');
    name.className = 'recipe-name';
    name.textContent = recipe.recipeName;
    //card.appendChild(name);

    const cardContent = `
                <div class="card">
                <img src="<%= recipe.image %>" alt="<%= recipe.recipeName %>">
                <!-- link to individual recipe function -->
                <div class="card-content">
                    <div class="card-title">
                        <!-- <%= recipe.recipeName %> -->
                        <h3>
                            <%= recipe.recipeName %>
                        </h3>
                        <div class="favourite-icon" onclick="">
                            <img src="/assets/outline-heart.png" alt="Save" onclick="addToSaved(<%= recipe.id %>)">
                        </div>
                        <div class="add-symbol">
                            <img src="/assets/add-symbol.png" id="open-popup" alt="Add to meal planner"
                                onclick="openPopup(<%= recipe.recipeName %>)">
                            <!-- <button class="add-symbol" onclick="openPopup()">+</button> -->
                            <div id="popup" class="popup-container">
                                <div class="popup">
                                    <span class="close-popup" id="close-popup" onclick="closePopup()">&times;</span>
                                    <h2>Select Meals</h2>
                                    <select id="day-options">
                                        <option value="Monday">Monday</option>
                                        <option value="Tuesday">Tuesday</option>
                                        <option value="Wednesday">Wednesday</option>
                                        <option value="Thursday">Thursday</option>
                                        <option value="Friday">Friday</option>
                                        <option value="Saturday">Saturday</option>
                                        <option value="Sunday">Sunday</option>
                                    </select>
                                    <select id="meal-options">
                                        <option value="Breakfast">Breakfast</option>
                                        <option value="Lunch">Lunch</option>
                                        <option value="Dinner">Dinner</option>
                                    </select>
                                    <button id="add-meal" onclick="addToPlanner()">Add Meal</button>
                                </div>
                            </div>
                        </div>
                        <strong>Recipe type:</strong>
                        <%= recipe.category %> <br>
                            <strong>Cook Time:</strong>
                            <%= recipe.time %> <br>
                                <!-- Make a method to return missing ingredients for the recipe -->
                                <!-- <strong>Missing ingredients:</strong> Chicken, Rice, Butter, Cream <br> -->
                                <div class="rating">
                                    <!-- make method to display the stars from <%= recipe.rating %> -->
                                    <span class="filled">☆</span>
                                    <span class="filled">☆</span>
                                    <span class="filled">☆</span>
                                    <span>☆</span>
                                    <span>☆</span>
                                </div>
                    </div>
                </div>
            </div>`;
            card.innerHTML = cardContent;

    
    // Create and set the recipeInfo display
    searchResults.appendChild(card);
}

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
function addToPlanner() {
    // Communicate with C++ method to add the recipe to the planner on the given day
    recipeID = currRecipeId;
    const dayOptions = document.getElementById('day-options');
    const mealOptions = document.getElementById('meal-options');
    const selectedDay = dayOptions.value;
    const selectedMeal = mealOptions.value;
    console.log("Recipe with ID " + recipeID + " added to planner on " + selectedDay + " for " + selectedMeal +  "!");
    let mealOption = [];
    mealOption.push(selectedDay, selectedMeal, recipeID);
    mealPlanner.push(mealOption);
    // for(let i=0; i<mealPlanner.length; i++){
        console.log(mealPlanner[0]+"\n");
        // console.log("Recipe with ID " + recipeID + " added to planner on " + selectedDay + " for " + selectedMeal +  "!");
    // }
    closePopup();
}

// Function to open the popup
function openPopup(recipeID) {
    currRecipeId = recipeID;
    popup.style.display = 'block';
}

// Function to close the popup
function closePopup() {
    popup.style.display = 'none';
}


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

