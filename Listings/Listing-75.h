#pragma once

#include "Listing-69.h"

#include <tuple>

template<typename... CallObjects>  // (1)
class StaticDistributorVoid
{
public:
    StaticDistributorVoid(CallObjects... objects) : callObjects(objects...) {}  // (2)
    auto& tuple() { return callObjects; }  // (3)

    template<typename... CallData>  // (4)
    void operator() (CallData... callData)
    {
        Distribute2(callObjects, callData...);
    }
private:
    std::tuple<CallObjects...> callObjects;  // (5)
};

