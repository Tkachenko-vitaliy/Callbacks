class Executor
{
public:
    void callbackHandler(int eventID);
    void operator() (int eventID);
};

using ptr_callback = void(*) (int, void*);
using ptr_callback_static = void(*) (int, Executor*);
using ptr_callback_method = void(Executor::*)(int);

void run(ptr_callback ptrCallback, void* contextData = nullptr)  // (1)
{
    int eventID = 0;
    ptrCallback(eventID, contextData);
}

void run(ptr_callback_static ptrCallback, Executor* contextData = nullptr) // (2)
{
    int eventID = 0;
    ptrCallback(eventID, contextData);
}

void run(Executor* ptrClientCallbackClass, ptr_callback_method ptrClientCallbackMethod) // (3)
{
    int eventID = 0;
    (ptrClientCallbackClass->*ptrClientCallbackMethod)(eventID);
}

void run(Executor callbackHandler) // (4)
{
    int eventID = 0;
    callbackHandler(eventID);
}
