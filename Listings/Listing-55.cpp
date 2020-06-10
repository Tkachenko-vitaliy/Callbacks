#include "Listing-28.h"
#include "Listing-54.h"

class Executor
{
public:
    static void staticCallbackHandler(int eventID, Executor* executor) {}
    void callbackHandler(int eventID) {}
    void operator() (int eventID) {}
};

void ExternalHandler(int eventID, void* somePointer) {}

int main()
{
    int capturedValue = 0;
    Initiator initiator;
    Executor executor;

    // Pointer to the external function
    initiator.setup(CallbackConverter<void(*)(int, void*), void*>(ExternalHandler, &executor));

    // Pointer to the static method 
    initiator.setup(CallbackConverter<void(*)(int, Executor*), Executor*>(Executor::staticCallbackHandler, &executor));

    // Pointer to the class member method 
    initiator.setup(CallbackConverter<Executor, void(Executor::*)(int)>(&executor, &Executor::callbackHandler));

    // Functional object
    initiator.setup(executor);

    // Lambda-expression
    initiator.setup([capturedValue](int eventID) {});
}
