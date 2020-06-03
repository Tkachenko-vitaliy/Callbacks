#include "Listing-50.h"
#include "Listing-68.h"
#include "Listing-69.h"
#include "Listing-70.h"

void ExternalHandler(int eventID, int contextID) // (1)
{
}

struct FO
{
    void callbackHandler(int eventID, int contextID) {}
    void operator() (int eventID, int contextID) {}
};

int main()
{
    int eventID = 0, contextID = 1;  // (1)

    FO fo;
    auto lambda = [](int eventID, int contextID) {};
    CallbackToClass<FO, void(int, int)> cb2cl(&fo, &FO::callbackHandler);

    Distribute1(std::tuple(eventID, contextID), ExternalHandler, fo, cb2cl, lambda);
    Distribute2(std::tuple(ExternalHandler, fo, cb2cl, lambda), eventID, contextID);
    Distribute3(std::tuple(ExternalHandler, fo, cb2cl, lambda), std::tuple(eventID, contextID));
}
