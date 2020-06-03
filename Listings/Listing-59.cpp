#include "Listing-28.h"
#include "Listing-50.h"
#include "Listing-58.h"

class Executor
{
public:
    static void staticCallbackHandler(int eventID, Executor* executor) {}
    void callbackHandler(int eventID) {}
    void operator() (int eventID) {}
};

int main()
{
    Executor executor;

    Initiator initiator; // (1)
    initiator.setup(CallbackToClass<Executor, void(int)>(&executor, &Executor::callbackHandler));  // (2)
    initiator.run();

    Initiator<Executor> initiatorForClass;  // (3)
    initiatorForClass.setup(&Executor::callbackHandler); // (4)
    initiatorForClass.setupInstance(&executor); // (5)
    initiatorForClass.run();
}
