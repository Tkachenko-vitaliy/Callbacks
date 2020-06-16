#pragma once

#include <functional>

template<typename Function, typename Context, typename others>  // (0)
class CallbackConverter;

template<typename Function, typename Context, typename Return, typename ... ArgumentList>  // 1)
class CallbackConverter<Function, Context, Return(ArgumentList...)>  // (2)
{
public:
    CallbackConverter(Function argFunction = nullptr, Context argContext = nullptr)  // (3)
    {
        ptrFunction = argFunction; context = argContext;
    }

    Return operator() (ArgumentList... arguments)         // (4)
    {
        std::invoke(ptrFunction, context, arguments...);  // (5)   
    }
private:
    Function ptrFunction;      // (6)
    Context context;           // (7)
};

