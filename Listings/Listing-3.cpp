#include "Listing-0.h"

struct ÑontextData  // (1)
{
    //some context data
};

void callbackHandler(int eventID, void* somePointer)  // (2) 
{
    //It will be called by initiator
    ÑontextData* pContextData = (ÑontextData*)somePointer;   // (3) 
}

int main()  // (4)
{
    ÑontextData clientContext;  // (5)
    setup(callbackHandler, &clientContext);  // (6) 
    run(); // (7) 
    //Wait finish
}
