#include "Listing-69.h"

#include <functional>

void NativeHandler(int eventID)
{

}

void ExternalHandler(int eventID, int contextID)
{
}

struct FO
{
    void operator() (int eventID, int contextID) {}
    void callbackHandler(int eventID, int contextID) {}
};

int main()
{
    int eventID = 0, contextID = 0;
    FO fo;
    auto lambda = [](int eventID, int contextID) {};

    Distribute2(std::tuple(  // (1)
        NativeHandler,       // (2)
        std::bind(ExternalHandler, std::placeholders::_1, contextID),           // (3)
        std::bind(&FO::callbackHandler, fo, std::placeholders::_1, contextID),  // (4)
        std::bind(&FO::operator(), fo, std::placeholders::_1, contextID),       // (5)
        std::bind(lambda, std::placeholders::_1, contextID)                     // (6)
    ),
        eventID  // (7)
    );
}
