let ingredients = [];
let saved = [];
let planner = [];

function addIngredient() {
    const inputElem = document.getElementById("ingredient-input");
    const ingredient = inputElem.value.trim();
    if (ingredient && !ingredients.includes(ingredient)) { 
        ingredients.push(ingredient);
        //addNewIngredient();
        displayIngredients();
        inputElem.value = "";
    }
}

add_button = document.getElementById("add-button");
document.getElementById("ingredient-input").addEventListener('keydown', function(event) {
    if (event.keyCode === 13) {
        event.preventDefault();
        add_button.click();
    }
});


function displayIngredients() {
    const listElem = document.getElementById("ingredient-list");
    listElem.innerHTML = "";
    
    for (let ingredient of ingredients) {
        let li = document.createElement('li');
        li.textContent = ingredient;

        let deleteButton = document.createElement('button');
        deleteButton.textContent =  "\u2715";
        deleteButton.onclick = function() {
            removeIngredient(ingredient);
        };
        li.appendChild(deleteButton);

        listElem.appendChild(li);
    }
}

function removeIngredient(ingredient) {
    const index = ingredients.indexOf(ingredient);
    if (index > -1) {
        ingredients.splice(index, 1);
        displayIngredients();
    }
}

function searchRecipes() {
    // This function will communicate with the C++ backend
}

//GPT'D CODE
function displayCard(recipe) {
    const searchResults = document.getElementById('search-results');

    // Create the card container
    const card = document.createElement('div');
    card.className = 'recipe-card';

    // Create and set the RecipeInfo display
    const info = document.createElement('div');
    info.className = 'recipe-info';
    info.textContent = recipe.RecipeInfo; // assuming RecipeInfo is a string, adjust accordingly
    card.appendChild(info);

    // Create buttons for "Save" and "Add to Planner"
    const saveButton = document.createElement('button');
    saveButton.textContent = 'Save';
    saveButton.onclick = function() {
     addToSaved(recipe.recipeID);
    //"NativeMessageBox('the button was clicked')"
    };
    card.appendChild(saveButton);

    const addToPlannerButton = document.createElement('button');
    addToPlannerButton.textContent = 'Add to Planner';
    addToPlannerButton.onclick = function() {
        addToPlanner(recipe.recipeID, 'Monday'); // Example, adjust accordingly
    };
    card.appendChild(addToPlannerButton);

    // Append the card to search results
    searchResults.appendChild(card);
}

function getRecipeInfo(recipeID) {
    // This would communicate with your C++ method to get recipe information
    // Example return, adjust as needed:
    return {
        recipeName: "Sample Recipe Name",
        RecipeInfo: "RecipeName",
    };
}

// function displaySaved() {
//     const searchResults = document.getElementById('savedDisplayArea');

//     // Create the card container
//     const card = document.createElement('div');
//     card.className = 'recipe-card';

//     // Create and set the RecipeInfo display
//     const info = document.createElement('div');
//     info.className = 'recipe-info';
//     info.textContent = recipe.RecipeInfo; // assuming RecipeInfo is a string, adjust accordingly
//     card.appendChild(info);

//     // Create buttons for "Save" and "Add to Planner"
//     const saveButton = document.createElement('button');
//     saveButton.textContent = 'Save';
//     saveButton.onclick = function() {
//         addToSaved(recipe.recipeID);
//     };
//     card.appendChild(saveButton);

//     const addToPlannerButton = document.createElement('button');
//     addToPlannerButton.textContent = 'Add to Planner';
//     addToPlannerButton.onclick = function() {
//         addToPlanner(recipe.recipeID, 'Monday'); // Example, adjust accordingly
//     };
//     card.appendChild(addToPlannerButton);

//     // Append the card to search results
//     searchResults.appendChild(card);
// }

function getRecipeInfo(recipeID) {
    // This would communicate with your C++ method to get recipe information
    // Example return, adjust as needed:
    return {
        recipeName: "Sample Recipe Name",
        RecipeInfo: "RecipeName",
    };
}

function addToSaved(recipeID) {
    // Communicate with your C++ method to save the recipe
    console.log("Recipe with ID " + recipeID + " saved!");
    saved.push(recipe);
}

function addToPlanner(recipeID, day) {
    // Communicate with your C++ method to add the recipe to the planner on the given day
    console.log("Recipe with ID " + recipeID + " added to planner for " + day + "!");
    planner.push(recipe);
}

// Sample call to display a card (replace with actual method to get results from backend)
const sampleRecipe = getRecipeInfo(1);
displayCard(sampleRecipe);

/* GPTD */
function exportTableToCSV(filename) {
    var csv = [];
    var rows = document.querySelectorAll(".meal-planner tr");
    
    for (var i = 0; i < rows.length; i++) {
        var row = [], cols = rows[i].querySelectorAll("td, th");
        
        for (var j = 0; j < cols.length; j++) {
            // To handle commas in the content and multiline data:
            var cellContent = cols[j].innerText.replace(/"/g, '""');
            cellContent = '"' + cellContent + '"';
            row.push(cellContent);
        }
        
        csv.push(row.join(","));        
    }

    // Create CSV file and download
    var csvFile = new Blob([csv.join("\n")], { type: "text/csv" });
    var downloadLink = document.createElement("a");
    downloadLink.download = filename;
    downloadLink.href = window.URL.createObjectURL(csvFile);
    downloadLink.style.display = "none";
    document.body.appendChild(downloadLink);
    downloadLink.click();
}
