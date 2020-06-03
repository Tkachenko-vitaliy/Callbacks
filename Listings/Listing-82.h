#pragma once

#include <list>

template<typename unused> class DynamicDistributor; // (1)

template<typename Return, typename... ArgumentList>  // (2)
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
private:
    std::list< std::function<Return(ArgumentList ...)> > callObjects; // (5)
};

