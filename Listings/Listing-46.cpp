#include "Listing-28.h"
#include "Listing-45.h"

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
    UniArgument argument;

    Executor executor;
    int capturedValue = 0;

    using PtrExtFunc = void(*) (int, void*);
    argument = CallbackConverter<PtrExtFunc, void*>(ExternalHandler, &executor); // (1)

    using PtrStaticMethod = void(*) (int, Executor*);
    argument = CallbackConverter<PtrStaticMethod, Executor*>(Executor::staticCallbackHandler, &executor); // (2)

    argument = CallbackConverter<Executor, void(Executor::*)(int)>(&executor, &Executor::callbackHandler); // (3)

    argument = executor; // (4)

    argument = [capturedValue](int eventID) {/*Body of lambda*/}; // (5)
}
