#include <functional>

void External(int eventID) {};

int main()
{
    struct Call
    {
        void operator() (int eventID) {};
    } objectCall;

    std::function<void(int)> fnt;

    fnt = External;
    fnt = objectCall;
    fnt = [](int evetID) {};

    fnt(0);
}
