#pragma once

#include "SensorDef.h"

#include <map>
#include <thread>
#include <mutex>

namespace sensor
{

    class Observer
    {
    public:
        void start();
        void stop();
        void addAlert(SensorNumber number, SensorPointer pointer, SensorAlertCallback callback, SensorValue alertValue, AlertRule alertRule, CheckAlertTimeout checkTimeoutSet);
        void deleteAlert(SensorNumber number);
    private:

        struct Alert
        {
            Alert() {}
            Alert(SensorAlertCallback callback, SensorValue alertValue, AlertRule alertRule, SensorPointer sensor, CheckAlertTimeout checkTimeout) :
                callback(callback), alertValue(alertValue), alertRule(alertRule), sensor(sensor), checkTimeout(checkTimeout), currentTimeout(0)
            {

            }
            SensorAlertCallback callback;
            SensorValue alertValue;
            AlertRule alertRule;
            SensorPointer sensor;
            CheckAlertTimeout checkTimeout;
            CheckAlertTimeout currentTimeout;
        };

        std::map<SensorNumber, Alert> containerAlert;
        std::thread pollThread_;
        bool exit_;
        std::mutex mutex_;

        void poll();
    };

}; // namespace sensor
