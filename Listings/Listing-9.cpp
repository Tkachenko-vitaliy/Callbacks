class Executor;
using ptr_callback_static = void(*) (int, Executor*);

void run(ptr_callback_static ptrCallback, Executor* contextData = nullptr)
{
    int eventID = 0;
    //Some actions
    ptrCallback(eventID, contextData);
}
