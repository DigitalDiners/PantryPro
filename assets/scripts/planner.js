let currRecipeName;
let currId;

function getPlanner(){
    console.log("Creating planner...");
    try{
        const jsonMealPlanner = GetPlanner();
        console.log(jsonMealPlanner);
        const days = JSON.parse(jsonMealPlanner);
        
        for(let day of days){            
            displayMealCards(day);
        }
        
    }catch(error){
        console.error("Error fetching the planner:", error);
        alert("Failed to fetch meal planner. Please try again.");
    }
}

function displayMealCards(day){
    console.log("Displaying meal container");
    const plannerBox = document.getElementById("meal-planner-container");

    const dayCard = document.createElement('div');
    dayCard.className = 'day-card';
    
    const name = document.createElement('h4');
    name.id = 'day-name';
    name.textContent = day.name;
    dayCard.appendChild(name);

    const recipesContainer = document.createElement('div');
    recipesContainer.className = 'day-card-recipes';

    const breakfastRecipeContainer = document.createElement('div');
    breakfastRecipeContainer.className = 'day-card-recipe-container';
    const breakfastName = document.createElement('p');
    breakfastName.className = 'meal-name';
    breakfastName.textContent = "Breakfast";
    breakfastRecipeContainer.appendChild(breakfastName);

    const lunchRecipeContainer = document.createElement('div');
    lunchRecipeContainer.className = 'day-card-recipe-container';

    const lunchName = document.createElement('p');
    lunchName.className = 'meal-name';
    lunchName.textContent = "Lunch";
    lunchRecipeContainer.appendChild(lunchName);

    const dinnerRecipeContainer = document.createElement('div');
    dinnerRecipeContainer.className = 'day-card-recipe-container';

    const dinnerName = document.createElement('p');
    dinnerName.className = 'meal-name';
    dinnerName.textContent = "Dinner";
    dinnerRecipeContainer.appendChild(dinnerName);

    const breakfast = document.createElement('p');
    breakfast.className = 'meal';
    breakfast.textContent = day.breakfast;
    breakfastRecipeContainer.appendChild(breakfast);

    const lunch = document.createElement('p');
    lunch.className = 'meal';
    lunch.textContent = day.lunch;
    lunchRecipeContainer.appendChild(lunch);

    const dinner = document.createElement('p');
    dinner.className = 'meal';
    dinner.textContent = day.dinner;
    dinnerRecipeContainer.appendChild(dinner);

    // const snack = document.createElement('p');
    // snack.className = 'meal';
    // snack.textContent = day.snack;
    // dayCard.appendChild(snack);

    recipesContainer.appendChild(breakfastRecipeContainer);
    recipesContainer.appendChild(lunchRecipeContainer);
    recipesContainer.appendChild(dinnerRecipeContainer);
    dayCard.appendChild(recipesContainer);
    plannerBox.appendChild(dayCard);
}

window.onload = getPlanner;