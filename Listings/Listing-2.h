#pragma once

class Initiator  //(1)
{
public:
    using ptr_callback = void(*) (int, void*);    //(2)

    void setup(ptr_callback pPtrCallback, void* pContextData)    // (3)
    {
        ptrCallback = pPtrCallback; contextData = pContextData; // (4)
    }

    void run() //  (5)
    {
        int eventID = 0;
        //Some actions
        ptrCallback(eventID, contextData); // (6)
    }
private:
    ptr_callback ptrCallback = nullptr; // (7)
    void* contextData = nullptr; // (8)
};

