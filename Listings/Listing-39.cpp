int main()
{
    [](int eventID) {/*this is a body of lambda*/};  // (1)

    //The following object will be generated implicitly by the compiler from lambda declaration
    class Closure // (2)
    {
    public:
        void operator() (int eventID) // (3)
        {
            call_invoker(eventID);
        }

        static void  call_invoker(int eventID) { /*this is a body of lambda*/ }  // (4)

        using function_pointer = void(*)(int); // (5)

        operator function_pointer() const  // (6)
        {
            return call_invoker;
        }
    };

    //Conversion the closure object to the function pointer  
    Closure cl; // (7)
    using pointer_to_function = void(*)(int); // (8)
    pointer_to_function fptr = cl;  // (9)

    //Conversion a lambda to the function pointer
    fptr = [](int eventID) {/*this is a body of lambda*/}; // (10)
}
