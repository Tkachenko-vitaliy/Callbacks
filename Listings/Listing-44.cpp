#include "Listing-28.h"
#include "Listing-41.h"

class Executor  // (1)
{
public:
    static void staticCallbackHandler(int eventID, Executor* executor) {}
    void callbackHandler(int eventID) {}
    void operator() (int eventID) {}
};

void ExternalHandler(int eventID, void* somePointer) {} // (2)

int main()
{
    Executor executor;

    // (4) Pointer to the external function 
    Initiator<CallbackConverter<void(*)(int, void*), void*>> initExtFunction;
    initExtFunction.setup(CallbackConverter<void(*)(int, void*), void*>(ExternalHandler, &executor));

    // (9) Pointer to the static method 
    Initiator<CallbackConverter<void(*)(int, Executor*), Executor*>> initStaticMethod;
    initStaticMethod.setup(CallbackConverter<void(*)(int, Executor*), Executor*>(Executor::staticCallbackHandler, &executor));

    // (14) Pointer to the class member method
    Initiator<CallbackConverter<void(Executor::*)(int), Executor>> initMemberMethod;
    initMemberMethod.setup(CallbackConverter<void(Executor::*)(int), Executor> (&Executor::callbackHandler , &executor));

}
