#include "Listing-0.h"

ptr_callback ptrCallback = NULL;    // (2) 
void* contextData = NULL;              // (3) 

void setup(ptr_callback pPtrCallback, void* pContextData)  // (4)
{
    ptrCallback = ptrCallback;
    contextData = pContextData;
}

void run() // (5) 
{
    int eventID = 0;
    //Some actions
    ptrCallback(eventID, contextData); // (6) 
}