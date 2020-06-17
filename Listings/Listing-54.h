#pragma once

#include <functional>

template<typename unused>  // (1)
class CallbackConverter;

template<typename Context, typename Return, typename ... ArgumentList>  // (2)
class CallbackConverter<Return(Context, ArgumentList...)>               // (3)
{
public:

    using Function = Return(*)(Context, ArgumentList...);  // (4)

    CallbackConverter(Function argFunction = nullptr, Context argContext = nullptr)  // (5)
    {
        ptrFunction = argFunction; context = argContext;
    }

    Return operator() (ArgumentList... arguments)         // (6)
    {
        ptrFunction(context, arguments...);               // (7)   
    }
private:
    Function ptrFunction;          // (8)
    Context context;               // (9)
};

