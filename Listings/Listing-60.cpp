#include <functional>

void NativeHandler(int eventID) // (1)
{
    //here eventID is 10
}

void AnotherHandler(int contextID, int eventID) // (2)
{
    //here eventID is 1, contextID is 10;
}

int main()
{
    int eventID = 1; int contextID = 10;

    std::function<void(int)> fnt; // (3)
    fnt = NativeHandler; // (4)
    fnt(eventID); // (5) NativeHandler will be called

    fnt = std::bind(AnotherHandler, contextID, std::placeholders::_1); // (6)
    fnt(eventID); // (7) AnotherHandler will be called 
}
