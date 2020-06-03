#pragma once

class Executor;  //(1)

class Initiator  // (2)
{
public:
    using ptr_callback_static = void(*) (int, Executor*);   // (3)

    void setup(ptr_callback_static pPtrCallback, Executor* pContextData)  // (4)
    {
        ptrCallback = pPtrCallback; contextData = pContextData;  // (5)
    }

    void run()  //  (6)
    {
        int eventID = 0;
        //Some actions
        ptrCallback(eventID, contextData);  // (7)
    }

private:
    ptr_callback_static ptrCallback = nullptr;  // (8)
    Executor* contextData = nullptr;  // (9)
};

