#pragma once

#include "SensorDef.h"

namespace sensor
{

    class ISensor
    {
    public:
        virtual void setDriver(DriverPointer driverPointer) = 0;
        virtual DriverPointer getDriver() = 0;

        virtual double getValue() = 0;
        virtual bool isOperable() = 0;

        virtual ~ISensor() = default;

        static SensorPointer createSensor(SensorType type, SensorNumber number, DriverPointer driverPointer);
    };

}; //namespace sensor