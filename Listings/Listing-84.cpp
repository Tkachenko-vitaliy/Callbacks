#include "Listing-83.h"

struct FO
{
    int operator() (int eventID) { return 10; }
    int callbackHandler(int eventID) { return 100; }
};

int ExternalHandler(int eventID)
{
    return 0;
}

int main()
{
    int eventID = 0;

    FO fo;
    auto lambda = [](int eventID) { return 0; };
    auto binding = std::bind(&FO::callbackHandler, fo, std::placeholders::_1);

    DynamicDistributor<int(int)> distributor;    // (1)

    distributor.addCallObject(fo);               // (2)
    distributor.addCallObject(ExternalHandler);  // (3)
    distributor.addCallObject(binding);          // (4)
    distributor.addCallObject(lambda);           // (5)

    distributor(eventID); // (6)

    auto onReturnValue = [](int callResult) {};  // (7)
    distributor(onReturnValue, eventID);         // (8)
}
