#include "Listing-85.h"

struct FO
{
    int operator() (int eventID)
    {
        return 10;
    }
};

int ExternalHandler(int eventID)
{
    return 0;
}

struct ReceiverAddress  // (1)
{
    ReceiverAddress(int idGroup = 0, int idNumber = 0)
    {
        group = idGroup; number = idNumber;
    }

    int group;
    int number;
};

template<>
struct std::less<ReceiverAddress>  // (2)
{
    bool operator() (const ReceiverAddress& addr1, const ReceiverAddress& addr2) const
    {
        if (addr1.group < addr2.group)
        {
            return true;
        }
        else
        {
            if (addr1.group == addr2.group)
                return addr1.number < addr2.number;
            else
                return false;
        }
    }
};

int main()
{
    int eventID = 0;
    FO fo;
    auto lambda = [](int eventID) { return 0; };

    AddressDistributor<ReceiverAddress, std::less<ReceiverAddress>, int(int)> distributor;  // (3)

    distributor.addReceiver({ 1,1 }, fo);               // (4)
    distributor.addReceiver({ 2,2 }, ExternalHandler);  // (5)
    distributor.addReceiver({ 3,3 }, lambda);           // (6)

    distributor({ 1,1 }, eventID);  // (7)
    distributor({ 2,2 }, eventID);  // (8)
    distributor({ 3,3 }, eventID);  // (9)
}
