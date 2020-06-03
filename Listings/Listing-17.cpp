#include "Listing-16.h"

int main()
{
    Initiator initiator; // (1)
    CallbackHandler executor; // (2)
    initiator.setup(executor);  // (3)
    initiator.run();  // (4)
}
