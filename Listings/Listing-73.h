#pragma once

#include <tuple>

template <typename... CallObjects, std::size_t... indices, typename...CallData>  // (1)
auto  DistributeReturnImpl(std::tuple<CallObjects...>& callObjects, std::index_sequence<indices...>, CallData... callData) // (2)
{
    return std::tuple(std::get<indices>(callObjects)(callData...)...);  // (3)
}

template<typename... CallObjects, typename...CallData> // (4)
auto DistributeReturn(std::tuple<CallObjects...> callObjects, CallData... callData) // (5)
{
    return DistributeReturnImpl(  // (6)
        callObjects,  // (7)
        std::make_index_sequence<sizeof...(CallObjects)>(),  // (8)
        callData...); // (9)
}

