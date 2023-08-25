let ingredients = [];

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


function displayCard(recipe) {
    const searchResults = document.getElementById('search-results');

    const card = document.createElement('div');
    card.className = 'recipe-card';

    console.log("Recipe Name:", recipe.recipeName);

    const name = document.createElement('div');
    name.className = 'recipe-name';
    name.textContent = recipe.recipeName;
    card.appendChild(name);

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
