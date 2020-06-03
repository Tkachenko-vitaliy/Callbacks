#include "SensorControl.h"
#include "SensorInterface.h"
#include "DriverInterface.h"
#include "CommandQueue.h"
#include "Observer.h"
#include "Errors.h"
#include "SensorContainer.h"

using namespace sensor;

SensorControl::SensorControl():
    commandQueue_(new CommandQueue),
    observer_(new Observer),
    sensorContainer_(new SensorContainer),
    isInitialized_(false)
{
    
}

SensorControl::~SensorControl()
{
    shutDown();
    delete commandQueue_;
    delete observer_;
    delete sensorContainer_;
}

void SensorControl::initialize()
{
    commandQueue_->start();
    observer_->start();
    isInitialized_ = true;
}

void SensorControl::shutDown()
{
    commandQueue_->stop();
    observer_->stop();
    isInitialized_ = false;
}

void  SensorControl::assignDriver(DriverPointer driver)
{
    driver_ = driver;
}

DriverPointer  SensorControl::getAssignedDriver()
{
    return driver_;
}

DriverPointer SensorControl::getSensorDriver(SensorNumber number)
{
    return sensorContainer_->findSensor(number)->getDriver();
}

void SensorControl::addSensor(SensorType type, SensorNumber number)
{
    checkDriver();
    SensorPointer sensor = ISensor::createSensor(type, number, driver_);
    sensorContainer_->addSensor(number,sensor);
}

void SensorControl::deleteSensor(SensorNumber number)
{
    sensorContainer_->deleteSensor(number);
}

bool SensorControl::isSensorExist(SensorNumber number)
{
    return sensorContainer_->checkSensorExist(number).operator bool();
}

bool SensorControl::isSensorOperable(SensorNumber number)
{
    return sensorContainer_->findSensor(number)->isOperable();
}

SensorValue SensorControl::getSensorValue(SensorNumber number)
{
    return sensorContainer_->findSensor(number)->getValue();
}

void SensorControl::readSensorValues(SensorValueCallback callback)
{
    checkInitialize();
    
    sensorContainer_->forEachSensor([callback](SensorNumber number, SensorPointer sensor)
        {
            if (sensor->isOperable())
            {
                callback(number, sensor->getValue());
            }
        }
    );
}

void SensorControl::querySensorValue(SensorNumber number, SensorValueCallback callback)
{
    checkInitialize();
    commandQueue_->addCommand(number, sensorContainer_->findSensor(number), callback);
}

class FindMinMaxValue
{
public:
    enum MinMaxSign { MIN_VALUE = 0, MAX_VALUE = 1 };

    FindMinMaxValue(SensorNumber first, SensorNumber last, MinMaxSign sign) :
        sign_(sign), first_(first), last_(last), count_(0)
    {
        if (sign == MIN_VALUE)
        {
            result_ = std::numeric_limits<SensorValue>::max();
        }
        else
        {
            result_ = std::numeric_limits<SensorValue>::min();
        }

        arrayFunMinMax_[MIN_VALUE] = &FindMinMaxValue::CompareMin;
        arrayFunMinMax_[MAX_VALUE] = &FindMinMaxValue::CompareMax;
    }

    void operator()(SensorNumber number, SensorPointer sensor)
    {
        if ( sensor->isOperable() && (number >= first_ && number <= last_) )
        {
            (this->*arrayFunMinMax_[sign_])(sensor->getValue());
            count_++;
        }
    }

    SensorValue result() { return result_; }
    size_t count() { return count_; }
private:
    SensorNumber first_;
    SensorNumber last_;
    MinMaxSign sign_;
    SensorValue result_;
    size_t count_;

    using FunMinMax = void (FindMinMaxValue::*)(SensorValue value);

    void CompareMin(SensorValue value)
    {
        if (result_ > value)
        {
            result_ = value;
        }
    }
    void CompareMax(SensorValue value)
    {
        if (result_ < value)
        {
            result_ = value;
        }
    }

    FunMinMax arrayFunMinMax_[2];
};

SensorValue SensorControl::getMinValue(SensorNumber first, SensorNumber last)
{
    checkInitialize();

    FindMinMaxValue fmv(first, last, FindMinMaxValue::MIN_VALUE);
    sensorContainer_->forEachSensor(fmv);
    return fmv.result();
}

SensorValue SensorControl::getMaxValue(SensorNumber first, SensorNumber last)
{
    checkInitialize();

    FindMinMaxValue fmv(first, last, FindMinMaxValue::MAX_VALUE);
    sensorContainer_->forEachSensor(fmv);
    return fmv.result();
}

void SensorControl::setAlert(SensorNumber number, SensorAlertCallback callback, SensorValue alertValue, AlertRule alertRule, CheckAlertTimeout checkTimeoutSet)
{
    checkInitialize();
    observer_->addAlert(number, sensorContainer_->findSensor(number), callback, alertValue, alertRule, checkTimeoutSet);
}

void SensorControl::resetAlert(SensorNumber number)
{
    checkInitialize();
    observer_->deleteAlert(number);
}

void SensorControl::checkInitialize()
{
    if (!isInitialized_)
    {
        sensor_exception::throw_exception(SensorError::NotInitialized);
    }
}

void SensorControl::checkDriver()
{
    if (!driver_)
    {
        sensor_exception::throw_exception(SensorError::DriverIsNotSet);
    }
}
