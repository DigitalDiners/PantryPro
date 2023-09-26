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
    name.className = 'day-name';
    name.textContent = day.day;
    dayCard.appendChild(name);

    const horizontalRule = document.createElement('hr');
    horizontalRule.className = 'day-card-rule';
    dayCard.appendChild(horizontalRule);

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

    plannerBox.appendChild(dayCard);
}

window.onload = getPlanner;