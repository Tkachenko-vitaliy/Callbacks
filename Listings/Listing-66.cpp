#include "Listing-65.h"

#include <functional>

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
    using namespace std::placeholders;

    FO fo;  // (2)
    auto lambda = [](int eventID) {};  // (3)
    auto cb2cl = std::bind(&FO::callbackHandler, fo, _1);  // (4)

    int eventID = 0;  // (5)

    Distribute(eventID, ExternalHandler, fo, cb2cl, lambda);  // (6)
}
