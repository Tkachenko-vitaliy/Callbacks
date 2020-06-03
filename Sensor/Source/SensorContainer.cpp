#include "SensorContainer.h"
#include "Errors.h"

using namespace sensor;

void SensorContainer::addSensor(SensorNumber number, SensorPointer sensor)
{
    container_.insert({ number, sensor });
}

void SensorContainer::deleteSensor(SensorNumber number)
{
    container_.erase(number);
}

SensorPointer SensorContainer::findSensor(SensorNumber number)
{
    auto item = container_.find(number);
    if (item == container_.end())
    {
        sensor_exception::throw_exception(SensorError::UnknownSensorNumber);
    }
    return item->second;
}

SensorPointer SensorContainer::checkSensorExist(SensorNumber number)
{
    auto item = container_.find(number);
    if (item != container_.end())
    {
        return item->second;
    }
    else
    {
        return SensorPointer();
    }
}
