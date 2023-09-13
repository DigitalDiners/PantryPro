window.onload = createPlanner();

function createPlanner(){
    console.log("Creating planner...");
    try{
        const jsonMealPlanner = GetPlanner();
        const days = JSON.parse(jsonMealPlanner);
        
        let count = 0;
        for(let day of days){
            displayMealCards(day, count);
            count += 1;
        }

    }catch(error){
        console.error("Error fetching the planner:", error);
        alert("Failed to fetch meal planner. Please try again.");
    }
}

function displayMealCards(day, num){
    console.log("Displaying meal container");
    const plannerBox = document.getElementById("meal-planner-container");

    const dayCard = document.createElement('div');
    dayCard.className = 'day-card';
    
    const name = document.createElement('div');
    name.className = 'day-name';
    name.textContent = day.num.name;
    dayCard.appendChild(name);

    const rule = document.createElement('hr');
    dayCard.appendChild(rule)

    const breakfast = document.createElement('div');
    breakfast.className = 'meal';
    name.textContent = day.num.breakfast;
    dayCard.appendChild(breakfast);

    const lunch = document.createElement('div');
    lunch.className = 'meal';
    name.textContent = day.num.lunch;
    dayCard.appendChild(lunch);

    const dinner = document.createElement('div');
    dinner.className = 'meal';
    name.textContent = day.num.dinner;
    dayCard.appendChild(dinner);

    const snack = document.createElement('div');
    snack.className = 'meal';
    name.textContent = day.num.snack;
    dayCard.appendChild(snack);

    plannerBox.appendChild(dayCard)
}