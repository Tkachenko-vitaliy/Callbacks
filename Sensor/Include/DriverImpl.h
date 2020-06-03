#pragma once

#include "DriverInterface.h"

namespace sensor
{

    class DriverSimulation : public IDriver
    {
    public:
        enum ReadType { READ_SPOT = 0, READ_SMOOTH = 1, READ_DERIVATIVE = 2 };

        using OnReadValue = std::function<SensorValue(SensorNumber, ReadType)>;
        using OnOperable = std::function<bool(SensorNumber)>;

        void initialize() override;

        void setDefaultValue(SensorValue value);
        void setDefaultOperable(bool isOperable);
        void setReadValue(OnReadValue value);
        void setOperable(OnOperable operable);

        void activate(SensorNumber number) override;
        bool isOperable(SensorNumber number) override;

        SensorValue readSpot(SensorNumber number) override;
        SensorValue readSmooth(SensorNumber number) override;
        SensorValue readDerivative(SensorNumber number) override;

        static IDriver* create();

    protected:
        DriverSimulation();

    private:
        OnReadValue getValue_;
        OnOperable  getOperable_;
        SensorValue defaultValue_ = 0;
        bool defaultOperable_ = true;
    };

    class DriverUSB : public IDriver
    {
    public:
        void initialize() override;
        void activate(SensorNumber number) override;
        bool isOperable(SensorNumber number) override;

        SensorValue readSpot(SensorNumber number) override;
        SensorValue readSmooth(SensorNumber number) override;
        SensorValue readDerivative(SensorNumber number) override;

        static IDriver* create();

    protected:
        DriverUSB();
    };

    class DriverEthernet : public IDriver
    {
    public:
        void initialize() override;
        void activate(SensorNumber number) override;
        bool isOperable(SensorNumber number) override;

        SensorValue readSpot(SensorNumber number) override;
        SensorValue readSmooth(SensorNumber number) override;
        SensorValue readDerivative(SensorNumber number) override;

        static IDriver* create();

    protected:
        DriverEthernet();
    };

}; //namespace sensor