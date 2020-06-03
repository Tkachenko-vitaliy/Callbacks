#include <functional>

int main()
{
    class Executor
    {
    public:
        void callbackHandler1(int eventID) {};
        void callbackHandler2(int eventID) {};
    };

    Executor executor;
    std::function<void(Executor*, int)> fnt; // (1)

    fnt = &Executor::callbackHandler1;  // (2)
    fnt = &Executor::callbackHandler2;  // (3)

    int eventID = 0;
    fnt(&executor, eventID); // (4)
}
