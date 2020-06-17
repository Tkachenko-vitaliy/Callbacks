#pragma once

#include <tuple>

template <typename CallData>
void Call(CallData& data)  // (1)
{
}

template <typename CallData, typename First, typename...Others>
void Call(CallData& data, First& first, Others&...rest)  // (2)
{
    std::apply(first, data);  // (3)
    Call(data, rest...);      // (4)
}

template <typename... CallData, typename... CallObjects>
void Distribute1(std::tuple<CallData...> data, CallObjects... objects)  // (5)

{
    Call(data, objects...);  // (6)
}

