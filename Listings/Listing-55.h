#pragma once

#include "Listing-54.h"

template<typename MemberType, typename ClassType, typename Return, typename...ArgumentList>  // (1) 
class CallbackConverter<MemberType ClassType::*, ClassType, Return(ArgumentList...)>  // (2) 
{
public:

    using MemberPointer = MemberType ClassType::*;

    CallbackConverter(MemberPointer methodPointer = nullptr, ClassType* classPointer = nullptr)  // (4) 
    {
        ptrClass = classPointer; ptrMethod = methodPointer;
    }

    Return operator()(ArgumentList... arguments)  // (5) 
    {
        (ptrClass->*ptrMethod)(arguments...);     // (6) 
    }
private:
    ClassType* ptrClass;                // (7) 
    MemberPointer ptrMethod;            // (8) 
};

