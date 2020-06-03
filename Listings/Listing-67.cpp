#include <utility>
#include <map>

template<typename...First, typename...Second>
void init(std::pair<First, Second>...)
{

}

int main()
{
	init(std::make_pair(1, 2), std::make_pair(3, 4), std::make_pair(0.3, 1e5));
}
