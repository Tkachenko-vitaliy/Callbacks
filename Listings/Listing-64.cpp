#include "Listing-50.h"
#include "Listing-63.h"

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
    CallbackToClass<FO, void()> cb2cl(&fo, &FO::callbackHandler);  // (4)

    Distribute(ExternalHandler, fo, cb2cl, lambda);  // (5)
}
