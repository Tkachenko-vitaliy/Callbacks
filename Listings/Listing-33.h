#pragma once

template <typename Data, typename Predicate> // (1)
void sort_bubble(Data* data, size_t size, Predicate less) // (2)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (less(data[j + 1], data[j])) // (3)
            {
                Data temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

