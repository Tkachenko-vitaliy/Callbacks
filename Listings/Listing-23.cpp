template<typename type, int size = 1>  // (1)
class StaticArray
{
public:
    type array[size];
};

template <typename TYPE>  // (2)
TYPE Sum(TYPE s2, TYPE s3)
{
    return s2 + s3;
}

int main()
{
    StaticArray<int, 1> someArray;  // (3)

    int a = 0; double x = 8; 
    Sum(a, a);  // (4)
    Sum<double> (a, x);  // (5)
}
