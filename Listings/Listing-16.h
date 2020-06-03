#pragma once

#include "Listing-15.h"

class Initiator // (1)
{
public:
    void setup(const CallbackHandler& callback) // (2)
    {
        callbackObject = callback;
    }

    void run() // (3)
    {
        int eventID = 0;
        //Some actions
        callbackObject(eventID); // (4)
    }

private:
    CallbackHandler callbackObject; // (5)
};

