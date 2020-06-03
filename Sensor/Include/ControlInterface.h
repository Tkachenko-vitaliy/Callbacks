#pragma once

#include "SensorDef.h"

namespace sensor
{

    class ISensorControl
    {
    public:
        virtual ~ISensorControl() = default;

        virtual void initialize() = 0;
        virtual void shutDown() = 0;
        virtual void assignDriver(DriverPointer driver) = 0;
        virtual DriverPointer getAssignedDriver() = 0;
        virtual DriverPointer getSensorDriver(SensorNumber number) = 0;
        virtual void addSensor(SensorType type, SensorNumber number) = 0;
        virtual void deleteSensor(SensorNumber number) = 0;
        virtual bool isSensorExist(SensorNumber number) = 0;
        virtual bool isSensorOperable(SensorNumber number) = 0;
        virtual SensorValue getSensorValue(SensorNumber number) = 0;
        virtual void querySensorValue(SensorNumber number, SensorValueCallback callback) = 0;
        virtual void readSensorValues(SensorValueCallback callback) = 0;
        virtual SensorValue getMinValue(SensorNumber first, SensorNumber last) = 0;
        virtual SensorValue getMaxValue(SensorNumber first, SensorNumber last) = 0;
        virtual void setAlert(SensorNumber number, SensorAlertCallback callback, SensorValue alertValue, AlertRule alertRule, CheckAlertTimeout checkTimeoutSet = 1) = 0;
        virtual void resetAlert(SensorNumber number) = 0;

        static ISensorControl* createControl();
    };

};
