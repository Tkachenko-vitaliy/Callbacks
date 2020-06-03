#include "Listing-2.h"

struct �ontextData // (1)
{
    //some context data
};

void callbackHandler(int eventID, void* somePointer) // (2) 
{
    //It will be called by initiator
    �ontextData* pContextData = static_cast<�ontextData*>(somePointer); // (3) cast to context
}

int main() // (4)
{
    Initiator  initiator;  // (5)
    �ontextData clientContext; // (6)
    initiator.setup(callbackHandler, &clientContext); // (7) callback setup 
    initiator.run(); // (8) initiator has been run
    //Wait finish
}
