#include "DriverImpl.h"

using namespace sensor;

DriverSimulation::DriverSimulation()
{

}

void DriverSimulation::setDefaultValue(SensorValue value)
{
    defaultValue_ = value;
}


void DriverSimulation::setDefaultOperable(bool isOperable)
{
    defaultOperable_ = isOperable;
}

void DriverSimulation::setReadValue(OnReadValue value)
{
    getValue_ = value;
}

void DriverSimulation::setOperable(OnOperable operable)
{
    getOperable_ = operable;
}

void DriverSimulation::initialize()
{

}

void DriverSimulation::activate(SensorNumber number)
{

}

bool DriverSimulation::isOperable(SensorNumber number)
{
    if (getOperable_)
    {
        return getOperable_(number);
    }
    else
    {
        return defaultOperable_;
    }
}

SensorValue DriverSimulation::readSpot(SensorNumber number)
{
    if (getValue_)
    {
        return getValue_(number, READ_SPOT);
    }
    else
    {
        return defaultValue_;
    }
}

SensorValue DriverSimulation::readSmooth(SensorNumber number)
{
    if (getValue_)
    {
        return getValue_(number, READ_SMOOTH);
    }
    else
    {
        return defaultValue_;
    }
}

SensorValue DriverSimulation::readDerivative(SensorNumber number)
{
    if (getValue_)
    {
        return getValue_(number, READ_DERIVATIVE);
    }
    else
    {
        return defaultValue_;
    }
}

IDriver* DriverSimulation::create()
{
    return new DriverSimulation;
}

DriverUSB::DriverUSB()
{

}

void DriverUSB::initialize()
{
    //TODO: need to be implemented
}

void DriverUSB::activate(SensorNumber number)
{
    //TODO: need to be implemented
}

bool DriverUSB::isOperable(SensorNumber number)
{
    //TODO: need to be implemented
    return true;
}

SensorValue DriverUSB::readSpot(SensorNumber number)
{
    //TODO: need to be implemented
    return 0;
}

SensorValue DriverUSB::readSmooth(SensorNumber number)
{
    //TODO: need to be implemented
    return 0;
}

SensorValue DriverUSB::readDerivative(SensorNumber number)
{
    //TODO: need to be implemented
    return 0;
}

IDriver* DriverUSB::create()
{
    return new DriverUSB;
}

DriverEthernet::DriverEthernet()
{

}

void DriverEthernet::initialize()
{
    //TODO: need to be implemented
}

void DriverEthernet::activate(SensorNumber number)
{
    //TODO: need to be implemented
}

bool DriverEthernet::isOperable(SensorNumber number)
{
    //TODO: need to be implemented
    return true;
}

SensorValue DriverEthernet::readSpot(SensorNumber number)
{
    //TODO: need to be implemented
    return 0;
}


SensorValue DriverEthernet::readSmooth(SensorNumber number)
{
    //TODO: need to be implemented
    return 0;
}

SensorValue DriverEthernet::readDerivative(SensorNumber number)
{
    //TODO: need to be implemented
    return 0;
}

IDriver* DriverEthernet::create()
{
    return new DriverEthernet;
}
