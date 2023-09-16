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
            const jsonIngredients = GetIngredientsByRecipe(recipe.recipeId);
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
    searchResults.appendChild(card);
}