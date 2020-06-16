#include <memory>

template <typename unused>
class UniArgument;

template<typename Return, typename ... ArgumentList>
class UniArgument<Return(ArgumentList...)>  
{
private:
    struct Callable
    {
        virtual Return operator()(ArgumentList... arguments) = 0; 
    };

    std::unique_ptr<Callable> callablePointer;

    template <typename Argument>
    struct CallableObject : Callable
    {
        Argument storedArgument;

        CallableObject(Argument argument) : storedArgument(argument) { }

        Return operator() (ArgumentList... arguments) override
        {
            return std::invoke(storedArgument, arguments...);
        }
    };

public:
    Return operator() (ArgumentList... arguments)
    {
        return callablePointer->operator()(arguments...);
    }

    template <typename Argument>
    void operator = (Argument argument)
    {
        callablePointer.reset(new CallableObject<Argument>(argument));
    }
};

struct CallbackHandler
{
    void handler1(int eventID) {};
    bool handler2(int eventID, int contextID) { return false; };
};

int main()
{
    CallbackHandler callbackObject;

    UniArgument<void(CallbackHandler*, int)> argument1;       // (1)
    UniArgument<bool(CallbackHandler*, int, int)> argument2;  // (2)

    argument1 = &CallbackHandler::handler1;  // (3)
    argument2 = &CallbackHandler::handler2;  // (4)
    argument1(&callbackObject, 100);         // (5)
    argument2(&callbackObject, 0, 1);        // (6)
}