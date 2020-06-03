#include "Listing-10.h"

class Executor  // (1)
{
public:
    void callbackHandler(int eventID)  // (2)
    {
        //It will be called by initiator
    }
};

int main()  // (3)
{
    Initiator initiator;  // (4)
    Executor executor;  // (5)
    initiator.setup(&executor, &Executor::callbackHandler);  // (6)
    initiator.run();  // (7)
}
