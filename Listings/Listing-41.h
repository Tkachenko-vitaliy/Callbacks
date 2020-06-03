#pragma once

template<typename CallbackArgument>
class Initiator
{
public:
    Initiator() {}
    Initiator(const CallbackArgument& argument) : callbackHandler(argument) {}

    void setup(const CallbackArgument& argument)
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
    CallbackArgument callbackHandler;
};

