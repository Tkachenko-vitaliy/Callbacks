#include "Listing-2.h"

struct ContextData // (1)
{
    //some context data
};

void callbackHandler(int eventID, void* somePointer)                    // (2) 
{
    //It will be called by initiator
    ContextData* pContextData = static_cast<ÑontextData*>(somePointer); // (3) cast to context
    //Do something here
}

int main() // (4)
{
    Initiator  initiator;                             // (5)
    ÑontextData clientContext;                        // (6)
    initiator.setup(callbackHandler, &clientContext); // (7) callback setup 
    initiator.run(); // (8) initiator has been run
    //Wait finish
}
