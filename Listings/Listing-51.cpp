#include "Listing-48.h"
#include "Listing-50.h"

class FO // (1)
{
public:
    void callbackHandler(int eventID) {};
};

int main()
{
    int eventID = 0;
    FO fo;

    UniArgument<void(int)> argument; // (2)
    CallbackToClass<FO, void(int)> cb2cl(&fo, &FO::callbackHandler); // (3)
    argument = cb2cl; // (4)
    argument(eventID); // (5)
}
