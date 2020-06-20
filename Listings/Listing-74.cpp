#include "Listing-73.h"

struct FO
{
    int operator() (int eventID)
    {
        return 10;
    }

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

    auto results = DistributeReturn(std::tuple(fo, ExternalHandler, lambda), eventID);  // (1)

    int foRes = std::get<0>(results);         // (2)
    SResult ExtRes = std::get<1>(results);    // (3)
    double lambdaRes = std::get<2>(results);  // (4)

    auto [foRes1, ExtRes1, lambdaRes1] = results; // (5)
    auto [foRes2, ExtRes2, lambdaRes2] = DistributeReturn(std::tuple(fo, ExternalHandler, lambda), eventID); //(6)
}
