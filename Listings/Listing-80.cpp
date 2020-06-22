#include "Listing-69.h"
#include "Listing-75.h"

#include <tuple>

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

    using funptr_type = SResult(*)(int);
    using lambda_type = decltype(lambda);

    StaticDistributorVoid <FO, funptr_type, lambda_type> distributor1(fo, ExternalHandler, lambda);  // (1)

    StaticDistributorVoid distributor2(fo, ExternalHandler, lambda);  // (2)
}
