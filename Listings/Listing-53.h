#pragma once

#include <functional>

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

