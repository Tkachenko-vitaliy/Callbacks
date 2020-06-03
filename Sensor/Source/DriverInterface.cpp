#include "DriverInterface.h"
#include "DriverImpl.h"

using namespace sensor;

DriverPointer IDriver::createDriver(DriverType type)
{
    using CreateFunPtr = IDriver * (*)();

    static const CreateFunPtr arrayCreateFun[] =
    {
        DriverSimulation::create,     //DRIVER_SIMULATION
        DriverUSB::create,   //DRIVER_USB
        DriverEthernet::create //DRIVER_ETHERNET
    };

    size_t index = static_cast<size_t>(type);

    return DriverPointer(arrayCreateFun[index]());
}

