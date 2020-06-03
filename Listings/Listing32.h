#pragma once

template <typename Data> // (1)
void sort_bubble(Data* data, size_t size) // (2)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (data[j + 1] < data[j])
            {
                Data temp = data[j]; // (3)
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

