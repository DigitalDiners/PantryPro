#include "recipeAPI.h"

RecipeAPI::RecipeAPI(Recipe* recipe) : recipe_(recipe) {}

JSValueRef RecipeAPI::getId(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    return JSValueMakeNumber(ctx, api->recipe_->getId());
}

JSValueRef RecipeAPI::getName(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    JSStringRef str = JSStringCreateWithUTF8CString(api->recipe_->getName().c_str());
    JSValueRef result = JSValueMakeString(ctx, str);
    JSStringRelease(str);
    return result;
}

JSValueRef RecipeAPI::getAuthorId(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    return JSValueMakeNumber(ctx, api->recipe_->getAuthorId());
}

JSValueRef RecipeAPI::getCookTime(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    return JSValueMakeNumber(ctx, api->recipe_->getCookTime());
}

JSValueRef RecipeAPI::getPrepTime(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    return JSValueMakeNumber(ctx, api->recipe_->getPrepTime());
}

JSValueRef RecipeAPI::getTotalTime(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    return JSValueMakeNumber(ctx, api->recipe_->getTotalTime());
}

JSValueRef RecipeAPI::getDatePublished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    JSStringRef str = JSStringCreateWithUTF8CString(api->recipe_->getDatePublished().c_str());
    JSValueRef result = JSValueMakeString(ctx, str);
    JSStringRelease(str);
    return result;
}

JSValueRef RecipeAPI::getDescription(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    JSStringRef str = JSStringCreateWithUTF8CString(api->recipe_->getDescription().c_str());
    JSValueRef result = JSValueMakeString(ctx, str);
    JSStringRelease(str);
    return result;
}

JSValueRef RecipeAPI::getCategory(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    JSStringRef str = JSStringCreateWithUTF8CString(api->recipe_->getCategory().c_str());
    JSValueRef result = JSValueMakeString(ctx, str);
    JSStringRelease(str);
    return result;
}

JSValueRef RecipeAPI::getCalories(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception){
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    return JSValueMakeNumber(ctx, api->recipe_->getCalories());
}

JSValueRef RecipeAPI::getServings(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception){
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    return JSValueMakeNumber(ctx, api->recipe_->getServings());
}

JSValueRef RecipeAPI::getYieldQuantity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception){
    RecipeAPI* api = static_cast<RecipeAPI*>(JSObjectGetPrivate(thisObject));
    return JSValueMakeNumber(ctx, api->recipe_->getYieldQuantity());
}


