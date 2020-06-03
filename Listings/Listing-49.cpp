#include "Listing-48.h"

void ExternalHandler1(int eventID);                         // (1)
int   ExternalHandler2(int eventID, int contextID); // (2)

struct CallbackHandler // (3)
{
    void operator() (int eventID);
    bool operator() (int eventID, int contextID);
};

int main()
{
    int capturedValue = 100;
    CallbackHandler callbackObject;               // (4)

    UniArgument<void(int)> argument1;        // (5)
    UniArgument<bool(int, int)> argument2; // (6)

    argument1 = ExternalHandler1; // (7)
    argument2 = ExternalHandler2; // (8)

    argument1 = callbackObject;     // (9)    
    argument2 = callbackObject;    // (10)

    argument1 = [capturedValue](int eventID) {/*Do something*/}; // (11)
    argument2 = [capturedValue](int eventID, int contextID) { /*DoSomething*/return 0; };  // (12)

    argument1(3);                     // (13)
    int res = argument2(4, 5); // (14)

    return res;
}
