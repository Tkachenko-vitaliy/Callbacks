// SensorApi.cpp : Defines the exported functions for the DLL.
//

#include "SensorApi.h"
#include "ControlInterface.h"
#include "Errors.h"
#include "DriverImpl.h"
#include "EnumConverter.h"

#include <initializer_list>
#include <functional>
#include <memory>

using ControlPointer = std::unique_ptr<sensor::ISensorControl>;

thread_local ControlPointer g_SensorControl(sensor::ISensorControl::createControl());
thread_local sensor::DriverPointer g_DriverSimulation;
thread_local sensor::DriverPointer g_DriverUSB;
thread_local sensor::DriverPointer g_DriverEthernet;

ErrorCode initialize()
{
    ErrorCode error = ERROR_NO;

    try
    {
        g_SensorControl->initialize();
    }
    catch(sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }

    return error;
}

ErrorCode shutDown()
{
    ErrorCode error = ERROR_NO;

    try
    {
        g_SensorControl->shutDown();
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }

    return error;
}

void CreateDriver(sensor::DriverType driverType, sensor::DriverPointer& driverPointer)
{
    if (!driverPointer)
    {
        driverPointer = sensor::IDriver::createDriver(driverType);
        driverPointer->initialize();
    }
    g_SensorControl->assignDriver(driverPointer);
}

ErrorCode assignDriver(DriverType driverType)
{
    ErrorCode error = ERROR_NO;

    try
    {
        EnumConverter<sensor::DriverType> conv;
        conv.convert(driverType, { sensor::DriverType::Simulation, sensor::DriverType::Usb, sensor::DriverType::Ethernet});
        if (conv.error())
        {
            return ERROR_INVALID_ARGUMENT;
        }

        switch (conv.result())
        {
        case sensor::DriverType::Simulation:
        {
            CreateDriver(sensor::DriverType::Simulation, g_DriverSimulation);
        }
        break;

        case sensor::DriverType::Usb:
        {
            CreateDriver(sensor::DriverType::Usb, g_DriverUSB);
        }
        break;

        case sensor::DriverType::Ethernet:
        {
            CreateDriver(sensor::DriverType::Ethernet, g_DriverEthernet);
        }
        break;
        }
        
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }

    return error;
}

ErrorCode getAssignedDriver(DriverType* type)
{
    ErrorCode error = ERROR_NO;

    try
    {
        sensor::DriverPointer driver = g_SensorControl->getAssignedDriver();

        if (!driver)
        {
            return ERROR_DRIVER_IS_NOT_SET;
        }

        if (driver.get() == g_DriverSimulation.get())
        {
            *type = DRIVER_SIMULATION;
        }
        if (driver.get() == g_DriverUSB.get())
        {
            *type = DRIVER_SIMULATION;
        }
        if (driver.get() == g_DriverEthernet.get())
        {
            *type = DRIVER_ETHERNET;
        }
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }

    return error;
}

ErrorCode getSensorDriver(SensorNumber number, DriverType* type)
{
    ErrorCode error = ERROR_NO;

    try
    {
        sensor::DriverPointer driver = g_SensorControl->getSensorDriver(number);

        if (!driver)
        {
            return ERROR_DRIVER_IS_NOT_SET;
        }
        if (dynamic_cast<sensor::DriverSimulation*>(driver.get()))
        {
            *type = DRIVER_SIMULATION;
        }
        if (dynamic_cast<sensor::DriverUSB*>(driver.get()))
        {
            *type = DRIVER_USB;
        }
        if (dynamic_cast<sensor::DriverEthernet*>(driver.get()))
        {
            *type = DRIVER_ETHERNET;
        }
    }
    catch (sensor::sensor_exception & e)
    {
        error = static_cast<ErrorCode>(e.code());
    }

    return error;
}

ErrorCode addSensor(SensorType type, SensorNumber number)
{
    ErrorCode error = ERROR_NO;

    try
    {
        EnumConverter<sensor::SensorType> conv;
        conv.convert(type, { sensor::SensorType::Spot, sensor::SensorType::Smooth, sensor::SensorType::Derivative });
        if (conv.error())
        {
            return ERROR_INVALID_ARGUMENT;
        }
        g_SensorControl->addSensor(conv.result(), number);
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code()); 
    }

    return error;
}

ErrorCode deleteSensor(SensorNumber number)
{
    ErrorCode error = ERROR_NO;

    try
    {
        g_SensorControl->deleteSensor(number);
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }

    return error;
}
ErrorCode isSensorExist(SensorNumber number, int* isExist)
{
    ErrorCode error = ERROR_NO;

    try
    {
        bool bExist = g_SensorControl->isSensorExist(number);
        *isExist = bExist ? 1 : 0;
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }
    return error;
}

ErrorCode isSensorOperable(SensorNumber number, int* isOperable)
{
    ErrorCode error = ERROR_NO;

    try
    {
        bool bOperable = g_SensorControl->isSensorExist(number);
        *isOperable = bOperable ? 1 : 0;
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }
    return error;
}

ErrorCode getSensorValue(SensorNumber number, SensorValue* value)
{
    ErrorCode error = ERROR_NO;

    try
    {
        *value = g_SensorControl->getSensorValue(number);
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }
    return error;
}

ErrorCode querySensorValue(SensorNumber number, SensorValueCallback callback, void* pContextData)
{
    ErrorCode error = ERROR_NO;

    try
    {
       using namespace std::placeholders;
       g_SensorControl->querySensorValue(number,std::bind(callback,_1,_2, pContextData));
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }
    return error;
}

ErrorCode readSensorValues(SensorValueCallback callback, void* pContextData)
{
    ErrorCode error = ERROR_NO;

    try
    {
        using namespace std::placeholders;
        g_SensorControl->readSensorValues(std::bind(callback,_1,_2,pContextData));
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }
    return error;
}

ErrorCode getMinValue(SensorNumber first, SensorNumber last, SensorValue* value)
{
    ErrorCode error = ERROR_NO;

    try
    {
        *value = g_SensorControl->getMinValue(first, last);
    }
    catch (sensor::sensor_exception & e)
    {
        error = static_cast<ErrorCode>(e.code());
    }
    return error;
}

ErrorCode getMaxValue(SensorNumber first, SensorNumber last, SensorValue* value)
{
    ErrorCode error = ERROR_NO;

    try
    {
        *value = g_SensorControl->getMaxValue(first, last);
    }
    catch (sensor::sensor_exception & e)
    {
        error = static_cast<ErrorCode>(e.code());
    }
    return error;
}


ErrorCode setAlert(SensorNumber number, SensorAlertCallback callback, SensorValue alertValue, AlertRule alertRule, CheckAlertTimeout checkTimeoutSet, void* pContextData)
{
    ErrorCode error = ERROR_NO;

    try
    {
        EnumConverter<sensor::AlertRule> conv;
        conv.convert(alertRule, {sensor::AlertRule::More, sensor::AlertRule::Less});
        if (conv.error())
        {
            return ERROR_INVALID_ARGUMENT;
        }
        using namespace std::placeholders;
        g_SensorControl->setAlert(number, std::bind(callback,_1,_2, pContextData), alertValue, conv.result(), checkTimeoutSet);
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }
    return error;
}

ErrorCode resetAlert(SensorNumber number)
{
    ErrorCode error = ERROR_NO;

    try
    {
        g_SensorControl->resetAlert(number);
    }
    catch (sensor::sensor_exception& e)
    {
        error = static_cast<ErrorCode>(e.code());
    }
    return error;
}

ErrorCode setSimulateReadCallback(OnSimulateReadValue callback, void* pContextData)
{
    using namespace std::placeholders;

    if (!g_DriverSimulation)
    {
        return ERROR_NOT_SUPPORTED;
    }

    sensor::DriverSimulation* driver = dynamic_cast<sensor::DriverSimulation*>(g_DriverSimulation.get());
    if (callback)
    {
        driver->setReadValue(std::bind(callback, _1, _2, pContextData));
    }
    else
    {
        driver->setOperable(sensor::DriverSimulation::OnOperable());
    }
    

    return ERROR_NO;
}

ErrorCode setSimulateOperableCallback(OnSimulateOperable callback, void* pContextData)
{
    using namespace std::placeholders;

    if (!g_DriverSimulation)
    {
        return ERROR_NOT_SUPPORTED;
    }
    sensor::DriverSimulation* driver = dynamic_cast<sensor::DriverSimulation*>(g_DriverSimulation.get());
    if (callback)
    {
        driver->setOperable(std::bind(callback, _1, pContextData));
    }
    else
    {
        driver->setOperable(sensor::DriverSimulation::OnOperable());
    }
    

    return ERROR_NO;
}
