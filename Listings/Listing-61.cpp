#include <functional>

class CallbackHandler
{
public:
    void NativeHandler(int eventID)
    {
        //eventID = 1;
    }
    void AnotherHandler(int contextID, int eventID)
    {
        //eventID = 1, contextID = 10;
    }
};

int main()
{
    using namespace std::placeholders; // (1)

    int eventID = 1; int contextID = 10;
    CallbackHandler handler;

    std::function<void(CallbackHandler*, int)> fnt;
    fnt = &CallbackHandler::NativeHandler;
    fnt(&handler, eventID); // NativeHandler will be called

    fnt = std::bind(&CallbackHandler::AnotherHandler, _1, contextID, _2); // (2)
    fnt(&handler, eventID); // AnotherHandler will be called
}
