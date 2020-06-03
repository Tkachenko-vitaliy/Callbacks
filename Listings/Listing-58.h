#pragma once

#include <functional>

template<typename... unused>  // (1)
class Initiator  // (1)
{
public:
    template<typename CallbackArgument>
    void setup(const CallbackArgument& argument) // (2)
    {
        callbackHandler = argument;
    }

    void run()
    {
        int eventID = 0;
        //Some actions
        callbackHandler(eventID);
    }

private:
    std::function<void(int)> callbackHandler;  // (3)
};

template<typename ClassName>  // (1)
class Initiator<ClassName>
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


