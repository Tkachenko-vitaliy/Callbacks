#pragma once

#include <memory>

class UniArgument  // (1)
{
private:
    class Callable  // (2)
    {
    public:
        virtual void operator()(int) = 0;  // (3)
    };

    std::unique_ptr<Callable> callablePointer;  // (4)

    template <typename ArgType>
    class CallableObject : public Callable  // (5)
    {
    public:
        CallableObject(ArgType argument) : storedArgument(argument) { }  // (7)

        void operator() (int value) override  // (8)
        {
            storedArgument(value);  // (9)
        }
    private:
        ArgType storedArgument;  // (6)
    };

public:
    void operator() (int value)  // (10)
    {
        callablePointer->operator()(value);  // (11)
    }

    template <typename ArgType>
    void operator = (ArgType argument)  // (12)
    {
        callablePointer.reset(new CallableObject<ArgType>(argument));  // (13)
    }
};


