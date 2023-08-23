#include "RegisterCFunctions.h"

RegisterCFunctions::RegisterCFunctions()
{
	RegisterNativeCFunctions();
}

JSValueRef NativeMessageBox(JSContextRef ctx_, 
							JSObjectRef fnc_, 
							JSObjectRef thisObject_, 
							size_t argCount_, 
							const JSValueRef args_[], 
							JSValueRef* exception_)
{
	if (argCount_ != 1)
	{
		OutputDebugStringA("NativeMessageBox improperly called in javascript. Expected exactly 1 argument of type string.");
		return JSValueMakeNull(ctx_);
	}

	JSType argType = JSValueGetType(ctx_, args_[0]);
	if (argType != JSType::kJSTypeString)
	{
		OutputDebugStringA("NativeMessageBox improperly called in javascript with an argument that was not of type string.");
		return JSValueMakeNull(ctx_);
	}

	JSStringRef msgArgumentJSRef = JSValueToStringCopy(ctx_, args_[0], NULL);
	size_t length = JSStringGetLength(msgArgumentJSRef) + 1;
	std::unique_ptr<char[]> stringBuffer = std::make_unique<char[]>(length);
	JSStringGetUTF8CString(msgArgumentJSRef, stringBuffer.get(), length);
	MessageBoxA(NULL, stringBuffer.get(), "NativeMessageBox", 0);
	return JSValueMakeNull(ctx_);
}

void RegisterCFunctions::RegisterNativeCFunctions()
{
    cout<<"registering";
	JSContextRef ctx = view->js_context(); // Create a JavaScript String containing the name of our callback.
	JSStringRef name = JSStringCreateWithUTF8CString("NativeMessageBox");
	JSObjectRef func = JSObjectMakeFunctionWithCallback(ctx, name, NativeMessageBox); // Create a garbage-collected JavaScript function
	JSObjectRef globalObj = JSContextGetGlobalObject(ctx); // Get the global JavaScript object (aka 'window')
	JSObjectSetProperty(ctx, globalObj, name, func, 0, 0); // Store our function in the page's global JavaScript object so that it accessible from the page as 'OnButtonClick()'.
	JSStringRelease(name); // Release the JavaScript String we created earlier.
}