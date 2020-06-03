#pragma once

#include <memory>

template <typename unused>
class UniArgument;

template<typename Return, typename ... ArgumentList>
class UniArgument<Return(ArgumentList...)> // (1)
{
private:
    struct Callable
    {
        virtual Return operator()(ArgumentList... arguments) = 0; // (3)
    };

    std::unique_ptr<Callable> callablePointer;

    template <typename Argument>
    struct CallableObject : Callable
    {
        Argument storedArgument;

        CallableObject(Argument argument) : storedArgument(argument) { }

        Return operator() (ArgumentList... arguments) override // (8)
        {
            return storedArgument(arguments...); // (9)
        }
    };

public:
    Return operator() (ArgumentList... arguments)  // (10)
    {
        return callablePointer->operator()(arguments...); // (11)
    }

    template <typename Argument>
    void operator = (Argument argument)
    {
        callablePointer.reset(new CallableObject<Argument>(argument));
    }
};

