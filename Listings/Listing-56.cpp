#include "Listing-53.h"
#include "Listing-55.h"

class Executor
{
public:
    static void staticCallbackHandler(Executor* executor, int eventID) {}
    void callbackHandler(int eventID) {}
    void operator() (int eventID) {}
};

void ExternalHandler(void* somePointer, int eventID) {}

int main()
{
    int capturedValue = 0;
    Initiator initiator;
    Executor executor;

    // Pointer to the external function
    initiator.setup(CallbackConverter<void(void*, int)>(ExternalHandler, &executor));

    // Pointer to the static method 
    initiator.setup(CallbackConverter<void(Executor*, int)>(Executor::staticCallbackHandler, &executor));

    // Pointer to the class member method 
    initiator.setup(CallbackConverter<void(Executor::*)(int)>(&Executor::callbackHandler, &executor));

    // Functional object
    initiator.setup(executor);

    // Lambda-expression
    initiator.setup([capturedValue](int eventID) {});
}
