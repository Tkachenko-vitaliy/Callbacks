int main()
{
    int capture = 0;
    [capture](int eventID) {/*this is a body of lambda*/};

    //This object will be generated implicitly by the compiler from lambda declaration
    class Closure
    {
    public:
        Closure(int value) :capture(value) {}

        void operator() (int eventID)
        {
            /*this is a body of lambda*/
        }

        int capture; //captured value
    };
}
