#include "Listing-68.h"
#include "Listing-69.h"
#include "Listing-70.h"

#include <functional>

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
    using namespace std::placeholders;
    int eventID = 0, contextID = 1;  // (1)

    FO fo;
    auto lambda = [](int eventID, int contextID) {};
    auto cb2cl = std::bind(&FO::callbackHandler, fo, _1, _2);

    Distribute1(std::tuple(eventID, contextID), ExternalHandler, fo, cb2cl, lambda);
    Distribute2(std::tuple(ExternalHandler, fo, cb2cl, lambda), eventID, contextID);
    Distribute3(std::tuple(ExternalHandler, fo, cb2cl, lambda), std::tuple(eventID, contextID));
}
