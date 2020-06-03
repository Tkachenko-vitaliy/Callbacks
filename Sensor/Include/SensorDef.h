#pragma once

#include <functional>
#include <memory>

namespace sensor
{
    class ISensor;
    class IDriver;

    using SensorNumber = unsigned int;
    using SensorValue = double;
    using CheckAlertTimeout = unsigned int;

    enum class SensorType : uint32_t
    {
        Spot = 0,
        Smooth = 1,
        Derivative = 2,
    };

    enum class DriverType : uint32_t
    {
        Simulation = 0,
        Usb = 1,
        Ethernet = 2
    };

    enum class AlertRule : uint32_t   
    { 
        More = 0, 
        Less = 1 
    };

    using SensorPointer = std::shared_ptr<ISensor>;
    using DriverPointer = std::shared_ptr<IDriver>;
    using SensorValueCallback = std::function<void(SensorNumber, SensorValue)>;
    using SensorAlertCallback = std::function<CheckAlertTimeout(SensorNumber, SensorValue)>;

}; //namespace sensor