#pragma once

#include <list>
#include <functional>

template<typename unused> class DynamicDistributor; // (1)

template <typename Return, typename... ArgumentList>
class DynamicDistributor<Return(ArgumentList...)>
{
public:
    template <typename CallObject> // (3)
    void addCallObject(CallObject object)
    {
        callObjects.push_back(object);
    }

    void operator ()(ArgumentList... arguments) // (4)
    {
        for (auto& callObject : callObjects)
        {
            callObject(arguments...);
        }
    }

    template<typename CallbackReturn > // (1)
    void operator()(CallbackReturn callbackReturn, ArgumentList... arguments)
    {
        for (auto& callObject : callObjects)
        {
            callbackReturn(callObject(arguments...)); // (2)
        }
    }
private:
    std::list< std::function<Return(ArgumentList ...)> > callObjects;
};

