#include "SensorApi.h"
#include "Errors.h"

#include <iostream>
#include <thread>
#include <assert.h>
#include <exception>

void CheckError(ErrorCode code)
{
    if (code != ERROR_NO)
    {
        throw std::exception();
    }
}

void Initialize()
{
    assignDriver(DRIVER_SIMULATION);

    addSensor(SENSOR_SPOT, 1);
    addSensor(SENSOR_SMOOTH, 2);
    addSensor(SENSOR_DERIVATIVE, 3);
    addSensor(SENSOR_SPOT, 4);
    addSensor(SENSOR_SMOOTH, 5);
    addSensor(SENSOR_DERIVATIVE, 6);

    auto f = [](SensorNumber number, int, void*)->SensorValue {return number; };

    setSimulateReadCallback(f, nullptr);
   
    initialize();

    DriverType drvType;
    getAssignedDriver(&drvType);
    std::cout << "Driver type = " << drvType << std::endl;
}

void ReadValues()
{
    ErrorCode err = readSensorValues(
        [](SensorNumber number, SensorValue value, void*)
        {
            std::cout << "sensor " << number << " value " << value << std::endl;
        },
        nullptr
    );
    CheckError(err);
}

void ReadSingleValues(unsigned int count)
{
    for (SensorNumber sn = 1; sn <= count; sn++)
    {
        SensorValue value; 
        ErrorCode err = getSensorValue(sn, &value);
        CheckError(err);
        std::cout << "sensor " << sn << " value " << value << std::endl;
    }
}

void QueryValues()
{
    auto f = [](SensorNumber number, SensorValue value, void*)
    {
        std::cout << "sensor " << number << " value " << value << std::endl;
    };

    querySensorValue(1, f, nullptr);
    querySensorValue(2, f, nullptr);
    querySensorValue(3, f, nullptr);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
}

void CheckOperable()
{
    auto f = [](SensorNumber number, void*)
    {
        if (number > 3)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    };

    setSimulateOperableCallback(f, nullptr);
    ReadValues();
    setSimulateOperableCallback(nullptr, nullptr);
}

struct AlertData
{
    bool bStop = false; 
    unsigned int count = 0;
};

CheckAlertTimeout AlertTrigger(SensorNumber number, SensorValue value, void* pContext)
{
    AlertData* pAlertData = (AlertData*)pContext;
    std::cout << "ALERT sensor " << number << " value " << value << std::endl;
    pAlertData->count++;
    if (pAlertData->count == 2)
    {
        pAlertData->bStop = true;
        return 0;
    }
    else
    {
        return 1;
    }
    return 0;
}

void AlertValues()
{
    using namespace std::chrono_literals;

    AlertData data;
    data.bStop = false; data.count = 0;
    setAlert(1, AlertTrigger, 10, ALERT_MORE, 1, &data);

   auto f = [](SensorNumber number, int, void*)->SensorValue 
   {
       if (number == 1)
       {
           return (SensorValue)20;
       }
       else
       {
           return (SensorValue)number;
       }
   };

   setSimulateReadCallback(f, nullptr);

   std::chrono::seconds duration(50);

   while (!data.bStop)
   {
        std::this_thread::sleep_for(1s);
   }
}

void MinMax()
{
    auto f = [](SensorNumber number, int, void*)->SensorValue {return number; };

    setSimulateReadCallback(f, nullptr);

    SensorValue value; 
    getMinValue(1, 4, &value);
    std::cout << "Min value : " <<  value << std::endl;
    getMaxValue(1, 4, &value);
    std::cout << "Max value : " << value << std::endl;
}

void RunThread()
{
    assignDriver(DRIVER_SIMULATION);

    addSensor(SENSOR_SPOT, 1);
    addSensor(SENSOR_SMOOTH, 2);
    addSensor(SENSOR_DERIVATIVE, 3);
    addSensor(SENSOR_SPOT, 4);
    addSensor(SENSOR_SMOOTH, 5);
    addSensor(SENSOR_DERIVATIVE, 6);

    auto f = [](SensorNumber number, int, void*)->SensorValue {return number*10; };
    setSimulateReadCallback(f, nullptr);

    initialize();

    ReadValues();

    shutDown();
}

void Threads()
{
    std::thread thread(RunThread);
    thread.join();
}


void TestLibrary()
{
    Initialize();

    std::cout << "Read single values:" << std::endl;
    ReadSingleValues(3);

    std::cout << std::endl << "enumerate all:" << std::endl;
    ReadValues();

    std::cout << std::endl << "operable:" << std::endl;
    CheckOperable();

    std::cout << std::endl << "Query values: " << std::endl;
    QueryValues();

    std::cout << std::endl << "Alert: " << std::endl;
    AlertValues();

    std::cout << std::endl << "MinMax: " << std::endl;
    MinMax();

    std::cout << std::endl << "Threads: " << std::endl;
    Threads();
}