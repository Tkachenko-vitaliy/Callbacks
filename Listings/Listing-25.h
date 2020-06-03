#pragma once

template <typename CallbackArgument>
void run(CallbackArgument callbackHandler)
{
    int eventID = 0;
    //Some actions
    callbackHandler(eventID);
}

