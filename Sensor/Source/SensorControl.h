#pragma once

#include "ControlInterface.h"

#include <map>
#include <list>

namespace sensor
{

    class ISensor;
    class IDriver;
    class CommandQueue;
    class Observer;
    class SensorContainer;

    class SensorControl: public ISensorControl
    {
    public:
        SensorControl();
        ~SensorControl();

        void initialize() override;
        void shutDown() override;
        void assignDriver(DriverPointer driver) override;
        DriverPointer getAssignedDriver() override;
        DriverPointer getSensorDriver(SensorNumber number) override;
        void addSensor(SensorType type, SensorNumber number) override;
        void deleteSensor(SensorNumber number) override;
        bool isSensorExist(SensorNumber number) override;
        bool isSensorOperable(SensorNumber number) override;
        SensorValue getSensorValue(SensorNumber number) override;
        void querySensorValue(SensorNumber number, SensorValueCallback callback) override;
        void readSensorValues(SensorValueCallback callback) override;
        SensorValue getMinValue(SensorNumber first, SensorNumber last) override;
        SensorValue getMaxValue(SensorNumber first, SensorNumber last) override;
        void setAlert(SensorNumber number, SensorAlertCallback callback, SensorValue alertValue, AlertRule alertRule, CheckAlertTimeout checkTimeoutSet = 1) override;
        void resetAlert(SensorNumber number) override;

    private:
        SensorContainer* sensorContainer_;
        CommandQueue* commandQueue_;
        Observer* observer_;
        bool isInitialized_;
        DriverPointer driver_;

        void checkInitialize();
        void checkDriver();
    };

}; //namespace sensor
