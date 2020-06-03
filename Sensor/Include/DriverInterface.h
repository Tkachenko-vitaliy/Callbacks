#pragma once

#include "SensorDef.h"

namespace sensor
{

    class IDriver
    {
    public:
        virtual void initialize() = 0;
        virtual void activate(SensorNumber number) = 0;
        virtual bool isOperable(SensorNumber number) = 0;

        virtual SensorValue readSpot(SensorNumber number) = 0;
        virtual SensorValue readSmooth(SensorNumber number) = 0;
        virtual SensorValue readDerivative(SensorNumber number) = 0;

        virtual ~IDriver() = default;

        static DriverPointer createDriver(DriverType type);
    };

}; //namespace sensor