#include "Listing-53.h"
#include "Listing-54.h"

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
    using PtrExtFunc = void(*) (void*, int);
    initiator.setup(CallbackConverter<PtrExtFunc, void*, void(int)>(ExternalHandler, &executor));

    // Pointer to the static method 
    using PtrStaticMethod = void(*) (Executor*, int);
    initiator.setup(CallbackConverter<PtrStaticMethod, Executor*, void(int)>(Executor::staticCallbackHandler, &executor));

    // Pointer to the class member method 
    using PtrMember = void(Executor::*)(int);
    initiator.setup(CallbackConverter<PtrMember, Executor*, void(int)>(&Executor::callbackHandler, &executor));

    // Functional object
    initiator.setup(executor);

    // Lambda-expression
    initiator.setup([capturedValue](int eventID) {});
}
