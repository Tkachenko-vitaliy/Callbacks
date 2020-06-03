#pragma once

#include "SensorInterface.h"

namespace sensor
{

    class SensorAbstract : public ISensor
    {
    public:
        void setDriver(DriverPointer driverPtr) override;
        DriverPointer getDriver() override;
        bool isOperable() override;
    protected:
        SensorAbstract(SensorNumber assignedNumber, DriverPointer driverPointer);
        SensorNumber number;
        DriverPointer driverPointer;
    };

    class SensorSpot : public SensorAbstract
    {
    public:
        double getValue() override;

        static ISensor* create(SensorNumber assignedNumber, DriverPointer driverPointer);

    protected:
        SensorSpot(SensorNumber assignedNumber, DriverPointer driverPointer);
    };

    class SensorSmooth : public SensorAbstract
    {
    public:

        double getValue() override;

        static ISensor* create(SensorNumber assignedNumber, DriverPointer driverPointer);

    protected:
        SensorSmooth(SensorNumber assignedNumber, DriverPointer driverPointer);
    };

    class SensorDerivative : public SensorAbstract
    {
    public:
        double getValue() override;

        static ISensor* create(SensorNumber assignedNumber, DriverPointer driverPointer);

    protected:
        SensorDerivative(SensorNumber assignedNumber, DriverPointer driverPointer);
    };

}; //namespace sensor