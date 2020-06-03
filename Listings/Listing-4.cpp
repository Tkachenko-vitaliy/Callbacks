#include "Listing-2.h"

struct ÑontextData // (1)
{
    //some context data
};

void callbackHandler(int eventID, void* somePointer) // (2) 
{
    //It will be called by initiator
    ÑontextData* pContextData = static_cast<ÑontextData*>(somePointer); // (3) cast to context
}

int main() // (4)
{
    Initiator  initiator;  // (5)
    ÑontextData clientContext; // (6)
    initiator.setup(callbackHandler, &clientContext); // (7) callback setup 
    initiator.run(); // (8) initiator has been run
    //Wait finish
}
