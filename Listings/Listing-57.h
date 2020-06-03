#pragma once

#include <functional>

template<typename ClassName>  // (1)
class InitiatorForClass
{
public:
    template<typename CallbackArgument>
    void setup(const CallbackArgument& argument) // (2) 
    {
        callbackHandler = argument;
    }

    void setupInstance(ClassName* classObject) // (3) 
    {
        ptrClass = classObject;
    }

    void run() // (4)
    {
        int eventID = 0;
        //Some actions 
        callbackHandler(ptrClass, eventID); // (5)
    }

private:
    std::function<void(ClassName*, int)> callbackHandler;  // (6) 
    ClassName* ptrClass = nullptr; // (7)
};

