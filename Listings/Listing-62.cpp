#include "Listing-53.h"

void NativeHandler(int eventID)
{
    //eventID = 10
}

void AnotherHandler(int contextID, int eventID)
{
    //eventID = 10, contextID = 1;
}

int main()
{
    int eventID = 10; int contextID = 1;
    Initiator initiator; // (1)

    initiator.setup(NativeHandler); // (2)
    initiator.setup(std::bind(AnotherHandler, contextID, std::placeholders::_1)); // (3)

    initiator.run(); // (4)
}
