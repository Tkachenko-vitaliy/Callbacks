#pragma once

void Call()  // (1)
{
}

template < typename First, typename...Others>
void Call(First& first, Others...rest)  // (2)
{
    first();  // (3)
    Call(rest...);  // (4)
}

template <typename ... CallObjects>
void Distribute(CallObjects... objects)  // (5)
{
    Call(objects...);  // (6)
}

