#include "Listing-50.h"
#include "Listing-65.h"

void ExternalHandler(int eventID) // (1)
{
}

struct FO
{
    void callbackHandler(int eventID) {}
    void operator() (int eventID) {}
};

int main()
{

    FO fo;  // (2)
    auto lambda = [](int eventID) {};  // (3)
    CallbackToClass<FO, void(int)> cb2cl(&fo, &FO::callbackHandler);  // (4)

    int eventID = 0;  // (5)

    Distribute(eventID, ExternalHandler, fo, cb2cl, lambda);  // (6)
}
