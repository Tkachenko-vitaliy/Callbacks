#include "Listing-6.h"

class Executor  // (1)
{
public:
    Executor(Initiator* initiator)  // (2)
    {
        initiator->setup(callbackHandler, this);
    }

    static void callbackHandler(int eventID, Executor* executor)  // (3)
    {
        //It will be called by initiator
        executor->onCallbackHandler(eventID);  // (4) 
    }

private:
    void onCallbackHandler(int eventID)  // (5)
    {
        //Do what is necessary
    }
};

int main() // (6)
{
    Initiator initiator; // (7)
    Executor executor(&initiator);  // (8)
    initiator.run(); // (9)
    //Wait finish
}
