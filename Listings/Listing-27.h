#pragma once

template<typename Function, typename Context>  // (1)
class CallbackConverter // (2)
{
public:
    CallbackConverter(Function argFunction = nullptr, Context argContext = nullptr) // (3)
    {
        ptrFunction = argFunction; context = argContext;
    }

    void operator() (int eventID) // (4)
    {
        ptrFunction(eventID, context); // (5)
    }
private:
    Function ptrFunction;  // (6)
    Context context; // (7)
};


