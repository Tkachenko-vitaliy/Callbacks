#include "SensorInterface.h"
#include "SensorImpl.h"

using namespace sensor;

SensorPointer ISensor::createSensor(SensorType type, SensorNumber number, DriverPointer driverPointer)
{
    using CreateFunPtr = ISensor * (*)(SensorNumber number, DriverPointer driverPointer);

    static const CreateFunPtr arrayCreateFun[] =
    {
        SensorSpot::create,     //SENSOR_SPOT
        SensorSmooth::create,   //SENSOR_SMOOTH
        SensorDerivative::create //SENSOR_DERIVATIVE
    };

    size_t index = static_cast<uint32_t>(type);

    return SensorPointer(arrayCreateFun[index](number, driverPointer));
}

