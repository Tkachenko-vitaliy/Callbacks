#include <functional>

int main()
{
    std::function<void(int)> fnt;

    fnt(0); //Error: argument is not set. Exception will be thrown

    fnt = [](int) {};
    fnt(0); //Ok, argument is set

    //Check if the argument is set
    if (fnt)
    {
        fnt(0);
    }
}
