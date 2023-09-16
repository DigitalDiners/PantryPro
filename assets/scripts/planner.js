window.onload = createPlanner();

function createPlanner(){
    console.log("Creating planner...");
    try{
        
        const jsonMealPlanner = GetPlanner();
        console.log(jsonMealPlanner);
        //const jsonMealPlanner = '[{"name":"Monday","breakfast":"Food", "lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name":"Tuesday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name":"Wednesday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name":"Thursday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name":"Friday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name": "Saturday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"},{"name": "Sunday","breakfast":"Food","lunch":"MoreFood","dinner":"LessFood","snack":"None"}]';
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