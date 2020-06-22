#pragma once

#include "Listing-69.h"
#include "Listing-73.h"

#include <tuple>

template<bool ShouldReturnValue, typename... CallObjects>  // (1)
class StaticDistributor
{
public:
    StaticDistributor(CallObjects... objects) : callObjects(objects...) {}  // (2)
    auto& tuple() { return callObjects; }  // (3)

    template<typename... CallData>  // (4)
    auto operator() (CallData... callData)
    {
        if constexpr (ShouldReturnValue)  // (5)
            return DistributeReturn(callObjects, callData...);
        else                              // (6)
            return Distribute2(callObjects, callData...);
    }
private:
    std::tuple<CallObjects...> callObjects;
};

