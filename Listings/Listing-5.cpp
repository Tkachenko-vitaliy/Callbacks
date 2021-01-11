#include <stdio.h>

using ptr_callback = void(*) (int, void*);

void run(ptr_callback ptrCallback, void* contextData = nullptr)
{
    int eventID = 0;
    //Some actions
    ptrCallback(eventID, contextData);
}
