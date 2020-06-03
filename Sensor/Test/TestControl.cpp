#include "ControlInterface.h"
#include "DriverInterface.h"
#include "DriverImpl.h"

#include <iostream>
#include <thread>
#include <memory>


using namespace sensor;

void Initialize(ISensorControl* sensorControl)
{
    sensorControl->assignDriver(IDriver::createDriver(DriverType::Simulation));

    sensorControl->addSensor(SensorType::Spot, 1);
    sensorControl->addSensor(SensorType::Smooth, 2);
    sensorControl->addSensor(SensorType::Derivative, 3);
    sensorControl->addSensor(SensorType::Spot, 4);
    sensorControl->addSensor(SensorType::Smooth, 5);
    sensorControl->addSensor(SensorType::Derivative, 6);

    DriverPointer driver = sensorControl->getAssignedDriver();
    DriverSimulation* driverSimulation = dynamic_cast<DriverSimulation*>(driver.get());
    driverSimulation->setReadValue([](SensorNumber number, DriverSimulation::ReadType)
        {
            return number;
        }
    );

    sensorControl->initialize();
}

void ReadValues(ISensorControl* sensorControl)
{
    sensorControl->readSensorValues(
        [](SensorNumber number, SensorValue value)
        {
            std::cout << "sensor " << number << " value " << value << std::endl;
        }
    );
}

void ReadSingleValues(ISensorControl* sensorControl, unsigned int count)
{
    for (SensorNumber sn = 1; sn <= count; sn++)
    {
        std::cout << "sensor " << sn << " value " << sensorControl->getSensorValue(sn) << std::endl;
    }
}

void QueryValues(ISensorControl* sensorControl)
{
    auto f = [](SensorNumber number, SensorValue value)
    {
        std::cout << "sensor " << number << " value " << value << std::endl;
    };

    sensorControl->querySensorValue(1, f);
    sensorControl->querySensorValue(2, f);
    sensorControl->querySensorValue(3, f);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
}

void CheckOperable(ISensorControl* sensorControl)
{
    DriverPointer driver = sensorControl->getSensorDriver(1);
    DriverSimulation* driverSimulation = dynamic_cast<DriverSimulation*>(driver.get());

    driverSimulation->setOperable([](SensorNumber number)
        {
            if (number > 3)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    );
    ReadValues(sensorControl);
    driverSimulation->setOperable(nullptr);
}


void AlertValues(ISensorControl* sensorControl)
{
    using namespace std::chrono_literals;

    bool bStop = false; unsigned int count = 0;
    auto f = [&bStop, &sensorControl, &count](SensorNumber number, SensorValue value)
    {
        std::cout << "ALERT sensor " << number << " value " << value << std::endl;
        count++;
        if (count == 2)
        {
            bStop = true;
            return 0;
        }
        else
        {
            return 1;
        }
        return 0;
    };
    sensorControl->setAlert(1, f, 10, AlertRule::More);

    DriverPointer driver = sensorControl->getSensorDriver(1);
    DriverSimulation* driverSimulation = dynamic_cast<DriverSimulation*>(driver.get());
    driverSimulation->setReadValue([](SensorNumber number, DriverSimulation::ReadType type)
        {
            if (number == 1)
            {
                return (SensorValue)20;
            }
            else
            {
                return (SensorValue)number;
            }
        }
    );

    while (!bStop)
    {
        std::this_thread::sleep_for(3s);
    }
}

void MinMax(ISensorControl* sensorControl)
{
    DriverPointer driver = sensorControl->getSensorDriver(1);
    DriverSimulation* driverSimulation = dynamic_cast<DriverSimulation*>(driver.get());
    driverSimulation->setReadValue([](SensorNumber number, DriverSimulation::ReadType)
        {
            return number;
        }
    );

    std::cout << "Min value : " << sensorControl->getMinValue(1, 4) << std::endl;
    std::cout << "Max value : " << sensorControl->getMaxValue(1, 4) << std::endl;
}

void TestControl()
{
    std::unique_ptr<ISensorControl> sensorControl (ISensorControl::createControl());

    Initialize(sensorControl.get());

    std::cout << "Read single values:" << std::endl;
    ReadSingleValues(sensorControl.get(), 3);

    std::cout << std::endl << "enumerate all:" << std::endl;
    ReadValues(sensorControl.get());

    std::cout << std::endl << "operable:" << std::endl;
    CheckOperable(sensorControl.get());

    std::cout << std::endl << "Query values: " << std::endl;
    QueryValues(sensorControl.get());

    std::cout << std::endl << "Alert: " << std::endl;
    AlertValues(sensorControl.get());

    std::cout << std::endl << "MinMax: " << std::endl;
    MinMax(sensorControl.get());
}
