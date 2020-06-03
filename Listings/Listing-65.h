#pragma once

template <typename CallData>  // (1)
void Call(CallData& data)
{
}

template <typename CallData, typename First, typename...Others>  // (2)
void Call(CallData data, First& first, Others&...rest)
{
    first(data); // (3)
    Call(data, rest...); // (4)
}

template <typename CallData, typename ... CallObjects>  // (5)
void Distribute(CallData data, CallObjects... objects)
{
    Call(data, objects...); // (6)
}

