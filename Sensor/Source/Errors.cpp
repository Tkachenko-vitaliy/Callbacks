#include "Errors.h"

using namespace sensor;

const char* GetErrorString(SensorError errorCode)
{
    const char* errors[] =
    {
        "No Errors", //NoError
        "Module is not initialized",//NotInitialized
        "Unknown sensor type",      //UnknownSensorType
        "Unknown sensor number",    //UnknownSensorNumber
        "Sensor is not operable",   //SensorIsNotOperable
        "Driver is not assigned",   //DriverIsNotSet
        "Invalid argument",         //InvalidArgument
        "Operation is not supported",//NotSupportedOperation
        "Driver cannot be initialized",//InitDriverError
    };

    return errors[static_cast<std::size_t>(errorCode)];
}

sensor_exception::sensor_exception(SensorError error):code_(error)
{

}

SensorError sensor_exception::code() const noexcept
{
    return code_;
}

const char* sensor_exception::what() const noexcept
{
    return GetErrorString(code_);
}

void sensor_exception::throw_exception(SensorError error)
{
    throw sensor_exception(error);
}
