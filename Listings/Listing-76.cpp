#include "Listing-75.h"

#include <functional>

struct FO
{
    void operator() (int eventID) {}
    void callbackHandler(int eventID) {}
};

void ExternalHandler(int eventID) {}

int main()
{
    FO fo;
    int eventID = 0;
    auto lambda = [](int eventID) {};
    auto callbackToMethod = std::bind(&FO::callbackHandler, fo, std::placeholders::_1);

    StaticDistributorVoid distributor(ExternalHandler, fo, callbackToMethod, lambda); // (1)

    distributor(eventID); // (2)
}
