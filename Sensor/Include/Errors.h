#pragma once

#include <exception>
#include <cstdint>

namespace sensor
{

    enum class SensorError: uint32_t
    {
        NoError = 0,
        NotInitialized = 1,
        UnknownSensorType = 2,
        UnknownSensorNumber = 3,
        SensorIsNotOperable = 4,
        DriverIsNotSet = 5,
        InvalidArgument = 6,
        NotSupportedOperation = 7,
        InitDriverError = 8
    };

    class sensor_exception : public std::exception
    {
    public:
        sensor_exception(SensorError error);
        SensorError code() const noexcept;
        const char* what() const noexcept override;

        static void throw_exception(SensorError error);

    private:
        SensorError code_;
    };

}; //namespace sensor


