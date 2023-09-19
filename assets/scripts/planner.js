
function createPlanner(){
    console.log("Creating planner...");
    try{
        
        // const jsonMealPlanner = GetPlanner();
        // console.log(jsonMealPlanner);
        const jsonMealPlanner = '[{"name":"Monday","breakfast":"Food", "lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name":"Tuesday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name":"Wednesday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name":"Thursday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name":"Friday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name": "Saturday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name": "Sunday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"}]';
        const days = JSON.parse(jsonMealPlanner);
        // const days = JSON.parse(weeklyMealPlan);
        
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
    const plannerBox = document.getElementById('meal-planner-container');

    const dayCard = document.createElement('div');
    dayCard.className = 'day-card';
    
    const name = document.createElement('h4');
    name.className = 'day-name';
    name.textContent = day.name;
    dayCard.appendChild(name);

    const breakfast = document.createElement('p');
    breakfast.className = 'meal';
    breakfast.textContent = day.breakfast;
    dayCard.appendChild(breakfast);

    const lunch = document.createElement('p');
    lunch.className = 'meal';
    lunch.textContent = day.lunch;
    dayCard.appendChild(lunch);

    const dinner = document.createElement('p');
    dinner.className = 'meal';
    dinner.textContent = day.dinner;
    dayCard.appendChild(dinner);

    const snack = document.createElement('p');
    snack.className = 'meal';
    snack.textContent = day.snack;
    dayCard.appendChild(snack);

    plannerBox.appendChild(dayCard)
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

function addToJSON(day, meal, recipeName) {
    //assets/css/data/planner.json
    if (weeklyMealPlan[day] && weeklyMealPlan[day][meal] !== undefined) {
        if (weeklyMealPlan[day][meal] == null) {
            weeklyMealPlan[day][meal] = recipeName;
            console.log("Recipe: " + recipeName + " added to planner on " + day + " for " + meal + "!");
            // const jsonstring = JSON.stringify(weeklyMealPlan);
            let plannerArr = [recipeName, recipeId, day, meal];
            let done = AddToMealPlanner(plannerArr);
            if (done) {
                console.log("success");
            } else {
                console.log("fail");
            }
        } else {
            console.log("This slot is already filled");
        }
    } else {
        console.log("Invalid day or meal type");
    }
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

window.onload = createPlanner();
