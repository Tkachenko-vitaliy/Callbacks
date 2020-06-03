#include "Listing-25.h"
#include "Listing-27.h"
#include "Listing-28.h"

class Executor // (1)
{
public:
    static void staticCallbackHandler(int eventID, Executor* executor) {}
    void callbackHandler(int eventID) {}
    void operator() (int eventID) {}
};

void ExternalHandler(int eventID, void* somePointer)
{
    Executor* ptrClass = (Executor*)somePointer;
}

int main()
{
    Executor executor;
    int capturedValue = 0;

    // (2) External function 
    run(CallbackConverter<void(*)(int, void*), void*>(ExternalHandler, &executor));

    // (3) Static method
    run(CallbackConverter<void(*)(int, Executor*), Executor*>(Executor::staticCallbackHandler, &executor));

    // (4) Member merthod
    run(CallbackConverter<Executor, void(Executor::*)(int)>(&executor, &Executor::callbackHandler));

    // (5) Functional object
    run(executor);

    // (6) lambda-expression
    run([capturedValue](int eventID) {/*it will be called by initiator*/});
}
