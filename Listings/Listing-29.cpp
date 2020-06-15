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
    using FunctionPointer = void(*)(int, void*);
    using FunctionConverter = CallbackConverter<FunctionPointer, void*>;
    run(FunctionConverter(ExternalHandler, &executor));

    // (3) Static method
    using StaticPointer = void(*)(int, Executor*);
    using StaticConverter = CallbackConverter<StaticPointer, Executor*>;
    run(StaticConverter(Executor::staticCallbackHandler, &executor));

    // (4) Member merthod
    using MethodPointer = void(Executor::*)(int);
    using MethodConverter = CallbackConverter<MethodPointer, Executor>;
    run(MethodConverter(&Executor::callbackHandler, &executor));

    // (5) Functional object
    run(executor);

    // (6) lambda-expression
    auto lambda = [capturedValue](int eventID) {/*it will be called by initiator*/};
    run(lambda);
}
