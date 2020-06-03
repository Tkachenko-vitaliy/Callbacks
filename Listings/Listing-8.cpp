#include "Listing-0.h"

class Executor // (1)
{
public:
    Executor() // (2)
    {
        setup(callbackHandler, this);
    }

    static void callbackHandler(int eventID, void* somePointer) // (3)
    {
        //It will be called by initiator
        Executor* executor = static_cast<Executor*>(somePointer); // (4)
        executor->onCallbackHandler(eventID);
    }

private:
    void onCallbackHandler(int eventID) // (5)
    {
        //Do what is necessary
    }
};

int main() // (6)
{
    Executor executor; // (7)
    run();  // (8)
    //Wait finish
}
