#pragma once

#include <map>
#include <functional>
#include <stdexcept>

template <typename Address, typename AddressCompare, typename Function> class AddressDistributor;  // (1)

template <typename Address, typename AddressCompare, typename Return, typename... ArgumentList>    // (2)
class AddressDistributor<Address, AddressCompare, Return(ArgumentList...)>  // (3)
{
public:
    template<typename CallObject>  // (4)
    void addReceiver(Address address, CallObject object)
    {
        callObjects.insert({ address,object });
    }

    void deleteReceiver(Address address)  // (5)
    {
        callObjects.erase(address);
    }

    Return operator()(Address address, ArgumentList... arguments)  // (6)
    {
        auto iterator = callObjects.find(address);  // (7)
        if (iterator != callObjects.end())
        {
            return iterator->second(arguments...);  // (8)
        }
        else
        {
            throw std::invalid_argument("Invalid receiver address");  // (9)
        }
    }
private:
    std::map< Address, std::function<Return(ArgumentList...)>, AddressCompare  > callObjects;  // (10)
};

