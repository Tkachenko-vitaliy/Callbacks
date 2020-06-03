#pragma once

//General specialization
template <typename unused> // (1)
class function;

//Partial specialization
template<typename Return, typename ... ArgumentList > // (2)
class function<Return(ArgumentList...)>
{
public:

    Return operator()(ArgumentList... arguments) // (3)
    {
    }
};

