#include "Listing-10.h"
#include "Listing-12.h"

int main()
{
    Initiator initiator;
    Executor  executor;
    Executor1 executor1;
    Executor2 executor2;
    Executor3 executor3;

    initiator.setup(&executor, &Executor::callbackHandler1);    // (1)
    initiator.setup(&executor, &Executor::callbackHandler2);    // (2)
    initiator.setup(&executor1, &Executor::callbackHandler1);  // (3)
    initiator.setup(&executor1, &Executor::callbackHandler2);  // (4)
    initiator.setup(&executor2, &Executor::callbackHandler1);  // (5)
    initiator.setup(&executor2, &Executor::callbackHandler2);  // (6)

    //initiator.setup(&executor3, &Executor::callbackHandler1); //Incorrect, base class is ambiguous  // (7)
    //initiator.setup(&executor3, &Executor::callbackHandler2); //Incorrect, base class is ambiguous  // (8)

    initiator.setup((Executor1*)&executor3, &Executor::callbackHandler1);  // (9)
    initiator.setup((Executor1*)&executor3, &Executor::callbackHandler2);  // (10)
    initiator.setup((Executor2*)&executor3, &Executor::callbackHandler1);  // (11)
    initiator.setup((Executor2*)&executor3, &Executor::callbackHandler2);  // (12)
}

