#include "Listing-63.h"

#include <functional>

void ExternalHandler()  // (1)
{
}

struct FO
{
    void callbackHandler() {}
    void operator() () {}
};

int main()
{
    FO fo;  // (2)
    auto lambda = []() {};  // (3)
    auto cb2cl = std::bind(&FO::callbackHandler, fo);  // (4)

    Distribute(ExternalHandler, fo, cb2cl, lambda);  // (5)
}
