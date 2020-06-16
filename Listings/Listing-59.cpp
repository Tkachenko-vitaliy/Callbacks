#include "Listing-54.h"
#include "Listing-58.h"

class Executor
{
public:
    static void staticCallbackHandler(Executor* executor, int eventID) {}
    void callbackHandler(int eventID) {}
    void operator() (int eventID) {}
};

int main()
{
    Executor executor;

    Initiator initiator;  // (1)
    using PtrMember = void(Executor::*)(int);
    initiator.setup(CallbackConverter<PtrMember, Executor*, void(int)>
        (&Executor::callbackHandler, &executor));                       // (2)
    initiator.run();

    Initiator<Executor> initiatorForClass;                              // (3)
    initiatorForClass.setup(&Executor::callbackHandler);  // (4)
    initiatorForClass.setupInstance(&executor);                  // (5)
    initiatorForClass.run();
}

