#pragma once

#include <tuple>

template<std::size_t Index, typename CallObjects, typename... CallData>          // (1)
struct TupleIterator
{
    static void IterateTupleItem(CallObjects& callObjects, CallData...callData)  // (2)
    {
        const std::size_t idx = std::tuple_size_v<CallObjects> - Index;          // (3)
        std::get<idx>(callObjects)(callData...);                                 // (4)
        TupleIterator<Index - 1, CallObjects, CallData...>::IterateTupleItem(callObjects, callData...);  // (5)
    }
};

template<typename CallObjects, typename... CallData>  // (6)
struct TupleIterator<0, CallObjects, CallData...>     // (7)
{
    static void IterateTupleItem(CallObjects& callObjects, CallData... callData)  // (8)
    {
    }
};

template<typename... CallObjects, typename... CallData>                         // (9)
void Distribute2(std::tuple<CallObjects...> callObjects, CallData... callData)  // (10)
{
    TupleIterator                    // (11) 
        <
        sizeof...(CallObjects),      // (12)
        std::tuple<CallObjects...>,  // (13)
        CallData...                  // (14)
        >
        ::IterateTupleItem(callObjects, callData...);  // (15)
}

