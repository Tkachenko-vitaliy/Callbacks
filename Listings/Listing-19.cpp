#include <iostream>

int Calculate(int a, int b)
{
    return a + b;
}

int main()
{
    int a, b;
    std::cin >> a >> b;
    int result = Calculate(a, b);
    std::cout << result;
}
