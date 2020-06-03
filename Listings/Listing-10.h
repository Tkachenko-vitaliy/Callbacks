#pragma once

class Executor;  // (1)

class Initiator  // (2)
{
public:
    using ptr_callback_method = void(Executor::*)(int);  // (3) 

    void setup(Executor* argCallbackClass, ptr_callback_method argCallbackMethod)  // (4)
    {
        ptrCallbackClass = argCallbackClass; ptrCallbackMethod = argCallbackMethod;  // (5)
    }

    void run()  // (6)
    {
        int eventID = 0;
        //Some actions
        (ptrCallbackClass->*ptrCallbackMethod)(eventID);  // (7)
    }

private:
    Executor* ptrCallbackClass = nullptr;  // (8)
    ptr_callback_method ptrCallbackMethod = nullptr;  //(9)
};

