#pragma once

template <typename CallbackArgument, typename Context>
void run(CallbackArgument callbackHandler, Context* context)
{
    int eventID = 0;
    //Some actions
    callbackHandler(eventID, context);
}

