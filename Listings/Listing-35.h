#pragma once

template <typename Data> // (1)
struct default_less
{
    bool operator()(const Data& x, const Data& y) // (2)
    {
        return x < y;
    }
};

template <typename Data, typename Predicate = default_less<Data>> // (3)
void sort_bubble(Data* data, size_t size, Predicate less = Predicate()) // (4)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (less(data[j + 1], data[j]))
            {
                Data temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

