#include "MyApp.h"
#include "recipe.h"
#include "recipeDatabase.h"
#include "review.h"
#include "mealPlanner.h"
#include <AppCore/JSHelpers.h>
#include <Ultralight/Ultralight.h>
#include "timer.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

std::vector<int> savedRecipes;
std::vector<int> featuredRecipes;
MealPlanner mealPlanner;
//have a thing to hold the last search which will be sent to the js on open

MyApp::MyApp()
{
  ///
  /// Create our main App instance.
  ///
  app_ = App::Create();

  ///
  /// Create a resizable window by passing by OR'ing our window flags with
  /// kWindowFlags_Resizable.
  ///
  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
                           false, kWindowFlags_Titled | kWindowFlags_Resizable);

  ///
  /// Create our HTML overlay-- we don't care about its initial size and
  /// position because it'll be calculated when we call OnResize() below.
  ///
  overlay_ = Overlay::Create(window_, 1, 1, 0, 0);

  ///
  /// Force a call to OnResize to perform size/layout of our overlay.
  ///
  OnResize(window_.get(), window_->width(), window_->height());

  ///
  /// Load a page into our overlay's View
  ///
  overlay_->view()->LoadURL("file:///app.html");

  ///
  /// Register our MyApp instance as an AppListener so we can handle the
  /// App's OnUpdate event below.
  ///
  app_->set_listener(this);

  ///
  /// Register our MyApp instance as a WindowListener so we can handle the
  /// Window's OnResize event below.
  ///
  window_->set_listener(this);

  ///
  /// Register our MyApp instance as a LoadListener so we can handle the
  /// View's OnFinishLoading and OnDOMReady events below.
  ///
  overlay_->view()->set_load_listener(this);

  ///
  /// Register our MyApp instance as a ViewListener so we can handle the
  /// View's OnChangeCursor and OnChangeTitle events below.
  ///
  overlay_->view()->set_view_listener(this);
}

MyApp::~MyApp()
{
}

void MyApp::Run()
{
  app_->Run();
}

void MyApp::OnUpdate()
{
  ///
  /// This is called repeatedly from the application's update loop.
  ///
  /// You should update any app logic here.
  ///
}

void MyApp::OnClose(ultralight::Window *window)
{
  app_->Quit();
}

void MyApp::OnResize(ultralight::Window *window, uint32_t width, uint32_t height)
{
  ///
  /// This is called whenever the window changes size (values in pixels).
  ///
  /// We resize our overlay here to take up the entire window.
  ///
  overlay_->Resize(width, height);
}

void MyApp::OnFinishLoading(ultralight::View *caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String &url)
{
  ///
  /// This is called when a frame finishes loading on the page.
  ///
}

void MyApp::SaveOnExit(){
  mealPlanner.Save();
}

std::string MyApp::removeQuotes(const std::string &input)
{
  std::string result = input;
  result.erase(std::remove(result.begin(), result.end(), '\"'), result.end());
  return result;
}

std::string escapeJsonString(const std::string& input) {
    std::ostringstream ss;
    for (auto c : input) {
        switch (c) {
            case '"': ss << "\\\""; break;
            case '\\': ss << "\\\\"; break;
            case '/': ss << "\\/"; break;
            case '\b': ss << "\\b"; break;
            case '\f': ss << "\\f"; break;
            case '\n': ss << "\\n"; break;
            case '\r': continue;  // Just skip the carriage return
            case '\t': ss << "\\t"; break;
            default: ss << c; break;
        }
    }
    return ss.str();
}

std::string MyApp::convertRecipesToJson(const std::vector<Recipe> &recipes)
{
  std::cout << "convertRecipesToJson called" << std::endl;

  std::stringstream ss;

  ss << "[";

  std::cout << "recipes.size(): " << recipes.size() << std::endl;
  RecipeDatabase recipeDB;

  Timer timer;
  timer.start();

  Timer imageTimer;
  imageTimer.start();
  std::vector<RecipeImage> imagesVector = recipeDB.getAllRecipeImagesForRecipes(recipes);
  imageTimer.stop();
  std::cout << "Elapsed time to get image: " << imageTimer.elapsedMilliseconds() << " ms" << std::endl;

  Timer reviewTimer;
  reviewTimer.start();
  std::vector<Review> reviewVector = recipeDB.getAllReviewsForRecipes(recipes);
  reviewTimer.stop();
  std::cout << "Elapsed time to get reviews: " << reviewTimer.elapsedMilliseconds() << " ms" << std::endl;
  
  bool isFirst = true;
  for (const Recipe &recipe : recipes) {
    if (!isFirst) ss << ",";
    isFirst = false;
    std::cout << "recipe: " << recipe.getName() << std::endl;



    RecipeImage image(0, 0, "");
    for (const RecipeImage& img : imagesVector) {
        if (img.getRecipeId() == recipe.getId()) {
            image = img;
            break;
        }
    }
    Review review(0, 0, 0, 0, "", "", "");
    for (const Review& stars : reviewVector) {
        if (stars.getRecipeId() == recipe.getId()) {
            review = stars;
            break;
        }
    }
    //add calories back here
    //add reviews back
    ss << "{ ";
    ss << "\"recipeId\": " << (std::to_string(recipe.getId())) << ",";
    ss << "\"recipeName\": \"" << (recipe.getName()) << "\",";
    ss << "\"recipeCalories\": \"" << (recipe.getCalories()) << "\",";
    ss << "\"firstRating\": \"" << (review.getRating()) << "\",";
    ss << "\"instructions\": \"" << escapeJsonString(recipe.getInstructions()) << "\",";
    ss << "\"recipeImageURL\": \"" << removeQuotes(image.getImageURL()) + "\"";
    ss << " }";
  }
  ss << "]";

  timer.stop();
  std::cout << "Elapsed time to create json of 50 recipes: " << timer.elapsedMilliseconds() << " ms" << std::endl;

  return ss.str();
}

JSValue MyApp::SearchRecipes(const JSObject &thisObject, const JSArgs &args)
{
  std::cout << "SearchRecipes called" << std::endl;

  std::vector<std::string> ingredients;
  if (args[0].IsArray())
  {
    JSArray ingredientArray = args[0].ToArray();
    for (size_t i = 0; i < ingredientArray.length(); i++)
    {
      ultralight::String jsStr = ingredientArray[i].ToString();
      ingredients.push_back(std::string(jsStr.utf8().data()));
    }
  }

  RecipeDatabase recipeDB;
  std::vector<Recipe> recipes = recipeDB.getRecipesBySearch(ingredients);
  std::string jsonRecipes = convertRecipesToJson(recipes);

  std::cout << "jsonRecipes: " << jsonRecipes.c_str() << std::endl;

  return JSValue(jsonRecipes.c_str());
}

JSValue MyApp::GetIngredientsByRecipe(const JSObject &thisObject, const JSArgs &args)
{
    std::cout << "GetIngredientsByRecipe called" << std::endl;

    int recipeId = args[0].ToInteger();
    RecipeDatabase recipeDB;
    std::vector<Ingredient> ingredients = recipeDB.getIngredientsByRecipe(recipeId);

    std::ostringstream jsonIngredients;
    
    jsonIngredients << "[";

    for (const Ingredient &ingredient : ingredients)
    {
        jsonIngredients << "{";
        jsonIngredients << "\"IngredientId\": " << ingredient.getIngredientId() << ", ";
        jsonIngredients << "\"Name\": \"" << escapeJsonString(ingredient.getIngredientName()) << "\"";
        jsonIngredients << "},";
    }

    if (!ingredients.empty()){
        std::string temp = jsonIngredients.str();
        temp.pop_back();
        jsonIngredients.str("");
        jsonIngredients.clear();
        jsonIngredients << temp;
    }

    jsonIngredients << "]";

    //std::cout << "jsonIngredients: " << jsonIngredients.str() << std::endl;

    return JSValue(jsonIngredients.str().c_str());
}

JSValue MyApp::GetReviewsByRecipe(const JSObject& thisObject, const JSArgs& args) {
    //std::cout << "GetReviewsByRecipe called" << std::endl;

    int recipeId = args[0].ToInteger();

    RecipeDatabase recipeDB;
    std::vector<Review> reviews = recipeDB.getReviewsByRecipeId(recipeId);

    std::string jsonReviews = "[";

    for (const Review& review : reviews) {
        jsonReviews += "{ ";
        jsonReviews += "\"reviewId\": " + removeQuotes(std::to_string(review.getReviewId())) + ",";
        jsonReviews += "\"recipeId\": " + removeQuotes(std::to_string(review.getRecipeId())) + ",";
        jsonReviews += "\"authorId\": " + removeQuotes(std::to_string(review.getAuthorId())) + ",";
        jsonReviews += "\"rating\": " + removeQuotes(std::to_string(review.getRating())) + ",";
        jsonReviews += "\"review\": \"" + removeQuotes(review.getReviewText()) + "\",";
        jsonReviews += "\"dateSubmitted\": \"" + removeQuotes(review.getDateSubmitted()) + "\",";
        jsonReviews += "\"dateModified\": \"" + removeQuotes(review.getDateModified()) + "\"";
        jsonReviews += " },";
    }
    if (jsonReviews.back() == ',') jsonReviews.pop_back();
    jsonReviews += "]";

    //std::cout << "jsonReviews: " << jsonReviews.c_str() << std::endl;

    return JSValue(jsonReviews.c_str());
}

void MyApp::SaveRecipe(const JSObject &thisObject, const JSArgs &args)
{
  std::cout << "Save Recipe called" << std::endl;
  bool saved = false;
  int recipeId = args[0];
  if (savedRecipes.size() != 0)
  {
    for (int recipe : savedRecipes)
    {
      std::cout << recipe << std::endl;
      if (recipe == recipeId)
      {
        // std::cout << "saved" << std::endl;
        saved = true;
      }
    }
    if (saved)
    {
      std::cout << "duplicate not saved" << std::endl;
    }
    else
    {
      savedRecipes.push_back(recipeId);
    }
    return;
  }
  else
  {
    savedRecipes.push_back(recipeId);
    std::cout << "saved" << std::endl;
  }
}

JSValue MyApp::GetSaved(const JSObject &thisObject, const JSArgs &args)
{
  std::cout << "Get saved called" << std::endl;
  std::vector<Recipe> returnSaved;
  // std::sort (savedRecipes.begin(), savedRecipes.end());
  // savedRecipes.erase(std::unique(savedRecipes.begin(), savedRecipes.end(), savedRecipes.end()));
  RecipeDatabase recipeDB;
  for (int recipe : savedRecipes)
  {
    // std::cout << recipe << std::endl;
    returnSaved.push_back(recipeDB.getRecipeById(recipe));
  }
  std::string jsonRecipes = convertRecipesToJson(returnSaved);

  return JSValue(jsonRecipes.c_str());
}

JSValue MyApp::GetAndrews(const JSObject &thisObject, const JSArgs &args)
{
  std::cout << "Get saved called" << std::endl;
  std::vector<int> andrewsList;
  andrewsList.push_back(496252);
  andrewsList.push_back(537453);
  andrewsList.push_back(537034);
  andrewsList.push_back(540717);
  std::vector<Recipe> returnAndrews;
  // std::sort (savedRecipes.begin(), savedRecipes.end());
  // savedRecipes.erase(std::unique(savedRecipes.begin(), savedRecipes.end(), savedRecipes.end()));
  RecipeDatabase recipeDB;
  for (int recipe : andrewsList)
  {
    // std::cout << recipe << std::endl;
    returnAndrews.push_back(recipeDB.getRecipeById(recipe));
  }
  std::string jsonRecipes = convertRecipesToJson(returnAndrews);

  return JSValue(jsonRecipes.c_str());
}

JSValue MyApp::ShowFeatured(const JSObject &thisObject, const JSArgs &args){
  std::cout<<"show featured called"<< std::endl;

  std::vector<Recipe> returnFeatured;
  RecipeDatabase recipeDB;
  std::vector<int> featuredRandom;

  if(featuredRecipes.size()==0){
  std::vector<int> featuredtemp;
    //method to recipedb to populate the array
    //filter so only one of each recipeId
    featuredtemp=recipeDB.getFeaturedRecipes();
    //sort and remove duplicates

    std::sort(featuredRecipes.begin(), featuredRecipes.end());
    featuredRecipes.erase(std::unique(featuredRecipes.begin(), featuredRecipes.end()), featuredRecipes.end());
    for (auto it = featuredRecipes.cbegin(); it != featuredRecipes.cend(); ++it) {
        std::cout << *it << ' ';
    }
    //push into global vector
    for(int temp:featuredtemp){
      featuredRecipes.push_back(temp);
    }
  }
std::cout<<"back from db"<<std::endl;
  //return random
  //method to get 10 random from the featuredRecipes arr and return
  for(int i=0;i<10;i++){
    int randomIndex = rand() % featuredRecipes.size();
    int tempRecipe = featuredRecipes[randomIndex];
    featuredRandom.push_back(tempRecipe);
  }
  std::cout<<"random chosen"<<std::endl;

  for(int recipe:featuredRandom){
    returnFeatured.push_back(recipeDB.getRecipeById(recipe));
  }
  std::cout<<"random pushed"<<std::endl;

  std::string jsonRecipes = convertRecipesToJson(returnFeatured);
  return JSValue(jsonRecipes.c_str());


  // SELECT recipes.* FROM recipes, reviews WHERE recipes.`recipeId` = reviews.`recipeId` AND reviews.rating = 5 AND recipes.category NOT LIKE 'Beverages' ORDER BY `datePublished` DESC LIMIT 100;

}

JSValue MyApp::AddToMealPlanner(const JSObject &thisObject, const JSArgs &args)
{
  std::cout << "Add to meal Planner called" << std::endl;

  std::vector<std::string> planned;

  ultralight::String jsName = (args[0].ToString());
  std::string recipeName = std::string(jsName.utf8().data());
  int recipeId = args[1];
  ultralight::String jsDay = (args[2].ToString());
  std::string day = std::string(jsDay.utf8().data());
  ultralight::String jsMeal = (args[3].ToString());
  std::string meal = std::string(jsMeal.utf8().data());
  std::cout<<recipeName<<std::endl;
  std::cout<<recipeId<<std::endl;
  std::cout<<day<<std::endl;
  std::cout<<meal<<std::endl;
  bool yes = mealPlanner.addToPlanner(recipeName, recipeId, day, meal);
  // std::cout << "made back to myapp"<< std::endl;
  return yes;

  
  // // If success with this function
  // return true;
  // // else
  // return false;
}

JSValue MyApp::GetPlanner(const JSObject& thisObject, const JSArgs& args) {
    std::cout << "GetPlanner called" << std::endl;


    std::string plannerJson = mealPlanner.getPlannerJson();

    std::cout << "Planner Json: " << plannerJson.c_str() << std::endl;

    return JSValue(plannerJson.c_str());
}


void MyApp::OnDOMReady(ultralight::View *caller,
                       uint64_t frame_id,
                       bool is_main_frame,
                       const String &url)
{
  std::cout << "OnDOMReady called" << std::endl;
  ///
  /// Set our View's JSContext as the one to use in subsequent JSHelper calls
  ///
  RefPtr<JSContext> context = caller->LockJSContext();
  SetJSContext(context->ctx());

  JSObject global = JSGlobalObject();

  global["GetPlanner"] = BindJSCallbackWithRetval(&MyApp::GetPlanner);
  global["SearchRecipes"] = BindJSCallbackWithRetval(&MyApp::SearchRecipes);

  // global["RecipeIngredients"] = BindJSCallbackWithRetval(&MyApp::RecipeIngredients);
  global["AddToMealPlanner"] = BindJSCallbackWithRetval(&MyApp::AddToMealPlanner);
  global["SaveRecipe"] = BindJSCallback(&MyApp::SaveRecipe);
  global["GetSaved"] = BindJSCallbackWithRetval(&MyApp::GetSaved);
  global["GetAndrews"] = BindJSCallbackWithRetval(&MyApp::GetAndrews);
  global["ShowFeatured"] = BindJSCallbackWithRetval(&MyApp::ShowFeatured);
  global["GetIngredientsByRecipe"] = BindJSCallbackWithRetval(&MyApp::GetIngredientsByRecipe);
  global["GetReviewsByRecipe"] = BindJSCallbackWithRetval(&MyApp::GetReviewsByRecipe);
}

void MyApp::OnChangeCursor(ultralight::View *caller,
                           Cursor cursor)
{
  ///
  /// This is called whenever the page requests to change the cursor.
  ///
  /// We update the main window's cursor here.
  ///
  window_->SetCursor(cursor);
}

void MyApp::OnChangeTitle(ultralight::View *caller,
                          const String &title)
{
  ///
  /// This is called whenever the page requests to change the title.
  ///
  /// We update the main window's title here.
  ///
  window_->SetTitle(title.utf8().data());
}
