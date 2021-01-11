#include "Listing-0.h"

struct ContextData  // (1)
{
    //some context data
};

void callbackHandler(int eventID, void* somePointer)        // (2) 
{
    //It will be called by initiator
    ContextData* pContextData = (ÑontextData*)somePointer;  // (3) 
    //Do something here

}

int main()                                   // (4)
{
    ContextData clientContext;               // (5)
    setup(callbackHandler, &clientContext);  // (6) 
    run();                                   // (7) 
    //Wait finish
}
