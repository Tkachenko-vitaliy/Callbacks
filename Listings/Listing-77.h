#pragma once

#include <tuple>

template<typename... CallObjects>  // (1)
class StaticDistributorReturn
{
public:
    StaticDistributorReturn(CallObjects... objects) : callObjects(objects...) {}  // (2)
    auto& tuple() { return callObjects; }  // (3)

    template<typename... CallData>  // (4)
    auto operator() (CallData... callData)
    {
        return DistributeReturn(callObjects, callData...);
    }
private:
    std::tuple<CallObjects...> callObjects;  // (5)
};

