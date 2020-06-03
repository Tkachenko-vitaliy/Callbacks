template<typename type, int size = 1>
class StaticArray
{
public:
    type array[size];
};

int main()
{
    StaticArray<int, 1> someArray; //array consists of 1 item
    //…
}