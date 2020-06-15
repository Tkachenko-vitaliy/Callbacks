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
    Executor executor; // (3)
    int capturedValue = 0;

    // (4)  Pointer to the external function 
    using PtrExtFunc = void(*) (int, void*); // (5)
    using CallbackExtFunction = CallbackConverter<PtrExtFunc, void*>; // (6)
    Initiator<CallbackExtFunction> initExtFunction; // (7)
    initExtFunction.setup(CallbackExtFunction(ExternalHandler, &executor)); // (8)

    // (9) Pointer to the static method 
    using PtrStaticMethod = void(*) (int, Executor*); // (10)
    using CallbacStaticMethod = CallbackConverter<PtrStaticMethod, Executor*>; // (11)
    Initiator<CallbacStaticMethod> initStaticMethod; // (12)
    initStaticMethod.setup(CallbacStaticMethod(Executor::staticCallbackHandler, &executor)); // (13)

    // (14) Pointer to the class member method
    using PtrMethod = void(Executor::*)(int); // (15)
    using CallbackMemberMethod = CallbackConverter<void(Executor::*)(int), Executor>; // (16)
    Initiator<CallbackMemberMethod> initMemberMethod; // (17)
    initMemberMethod.setup(CallbackMemberMethod(&Executor::callbackHandler , &executor)); // (18)

    // (19) Functional object 
    Initiator<Executor> initFunctionObject; // (20)
    initFunctionObject.setup(executor); // (21)

    // (22) Lambda-expression
    auto lambda = [capturedValue](int eventID) {/*Body of lambda*/};  // (23)
    Initiator<decltype(lambda)> initLambda(lambda); // (24)
}
