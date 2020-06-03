#include "SensorImpl.h"
#include "DriverInterface.h"

using namespace sensor;

SensorAbstract::SensorAbstract(SensorNumber assignedNumber, DriverPointer driverPtr):
    number(assignedNumber), driverPointer(driverPtr)
{
    driverPointer->activate(assignedNumber);
}

void SensorAbstract::setDriver(DriverPointer driverPtr)
{
    driverPointer = driverPtr;
}

DriverPointer SensorAbstract::getDriver()
{
    return driverPointer;
}

bool SensorAbstract::isOperable()
{
    return driverPointer->isOperable(number);
}

SensorSpot::SensorSpot(SensorNumber assignedNumber, DriverPointer driverPointer):
    SensorAbstract(assignedNumber,driverPointer)
{

}

double SensorSpot::getValue()
{
    return driverPointer->readSpot(number);
}

ISensor* SensorSpot::create(SensorNumber assignedNumber, DriverPointer driverPointer)
{
    return new SensorSpot(assignedNumber, driverPointer);
}

SensorSmooth::SensorSmooth(SensorNumber assignedNumber, DriverPointer driverPointer):
    SensorAbstract(assignedNumber,driverPointer)
{

}

double SensorSmooth::getValue()
{
    return driverPointer->readSmooth(number);
}

ISensor*  SensorSmooth::create(SensorNumber assignedNumber, DriverPointer driverPointer)
{
    return new SensorSmooth(assignedNumber, driverPointer);
}

SensorDerivative::SensorDerivative(SensorNumber assignedNumber, DriverPointer driverPointer):
    SensorAbstract(assignedNumber, driverPointer)
{

}

double SensorDerivative::getValue()
{
    return driverPointer->readDerivative(number);
}

ISensor* SensorDerivative::create(SensorNumber assignedNumber, DriverPointer driverPointer)
{
    return new SensorDerivative(assignedNumber, driverPointer);
}

