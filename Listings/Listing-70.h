#pragma once

#include <tuple>

template<std::size_t Index, typename CallObjects, typename CallData>            // (1)
struct TupleIterator3
{
    static void IterateTupleItem(CallObjects& callObjects, CallData& callData)  // (2)
    {
        const std::size_t idx = std::tuple_size_v<CallObjects> -Index;  // (3)
        std::apply(std::get<idx>(callObjects), callData);               // (4)
        TupleIterator3<Index - 1, CallObjects, CallData>::IterateTupleItem(callObjects, callData);  // (5)
    }
};

template<typename CallObjects, typename CallData>  // (6)
struct TupleIterator3<0, CallObjects, CallData>    // (7)
{
    static void IterateTupleItem(CallObjects& callObjects, CallData& callData)  // (8)
    {
    }
};

template<typename... CallObjects, typename... CallData>                                     // (9)
void Distribute3(std::tuple<CallObjects...> callObjects, std::tuple<CallData...> callData)  // (10)
{
    TupleIterator3                   // (11) 
        <
        sizeof...(CallObjects),      // (12)
        std::tuple<CallObjects...>,  // (13)
        std::tuple<CallData...>      // (14)
        >
        ::IterateTupleItem(callObjects, callData);  // (15)
}



