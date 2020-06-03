class Executor;
using ptr_method_callback_t = void(Executor::*)(int);

void run(Executor* ptrClientCallbackClass, ptr_method_callback_t ptrClientCallbackMethod)
{
    int eventID = 0;
    //Some actions
    (ptrClientCallbackClass->*ptrClientCallbackMethod)(eventID);
}
