#pragma once

#include "Listing-69.h"
#include "Listing-73.h"

#include <tuple>

template<typename... CallObjects>  // (1)
class StaticDistributor
{
public:
    StaticDistributor(CallObjects... objects) : callObjects(objects...) {}  // (2)
    auto& tuple() { return callObjects; }  // (3)

    template<typename... CallData>
    auto operator() (CallData... callData)  // (4)
    {

#define callObject std::get<0>(callObjects)          // (5)
#define callObjType decltype(callObject)             // (6)
#define callObjInstance std::declval<callObjType>()  // (7)
#define testCall callObjInstance(callData...)        // (8)
#define retType decltype(testCall)                   // (9)

        //if constexpr (std::is_same_v<void, decltype(std::declval<decltype(std::get<0>(callObjects))>()(callData...))>)  // (10)
        if constexpr (std::is_same_v<void, retType>)            // (11)
            return Distribute2(callObjects, callData...);       // (12)
        else
            return DistributeReturn(callObjects, callData...);  // (13)
    }
private:
    std::tuple<CallObjects...> callObjects;
};

