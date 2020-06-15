#pragma once

#include "Listing-27.h"

template<typename ClassName>  // (1) 
class CallbackConverter <void(ClassName::*)(int), ClassName>  // (2) 
{
public:
    using ClassMethod = void(ClassName::*)(int);  // (3) 

    CallbackConverter(ClassMethod methodPointer = nullptr, ClassName* classPointer = nullptr)  // (4) 
    {
        ptrClass = classPointer; ptrMethod = methodPointer;
    }

    void operator()(int eventID)          // (5) 
    {
        (ptrClass->*ptrMethod)(eventID);  // (6) 
    }
private:
    ClassName* ptrClass;    // (7) 
    ClassMethod ptrMethod;  // (8) 
};

