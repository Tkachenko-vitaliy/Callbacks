#include "Listing-73.h"
#include "Listing-77.h"

#include <functional>

struct FO
{
    int operator() (int eventID) { return 10; }
    int callbackHandler(int eventID) { return 0; }
};

struct SResult
{
    unsigned int code;
    const char* description;
};

SResult ExternalHandler(int eventID)
{
    return SResult{ 1, "this is an error" };
}

int main()
{
    FO fo;
    int eventID = 0;
    auto lambda = [](int eventID) { return 0.0; };
    auto callbackToMethod = std::bind(&FO::callbackHandler, fo, std::placeholders::_1);

    StaticDistributorReturn distributor(ExternalHandler, fo, callbackToMethod, lambda); // (1)

    auto [resExtHandler, resFoOperator, resFoMethod, resLambda] = distributor(eventID); // (2)
}
