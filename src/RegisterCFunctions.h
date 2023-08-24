#pragma once
#include <string>
#include <vector>
#include <AppCore/AppCore.h>
#include <map>
#include <memory>
#include <stdio.h>
#include <iostream>


using ultralight::JSObject;
using ultralight::JSArgs;
using ultralight::JSFunction;
using namespace ultralight;


class RegisterCFunctions{
public:
    RegisterCFunctions();

private:
void RegisterNativeCFunctions();

};
