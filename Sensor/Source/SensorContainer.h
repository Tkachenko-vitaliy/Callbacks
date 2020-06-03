#pragma once

#include "SensorDef.h"
#include "SensorInterface.h"

#include <map>

namespace sensor
{

    class SensorContainer
    {
    public:
        void addSensor(SensorNumber number, SensorPointer sensor);
        void deleteSensor(SensorNumber number);
        SensorPointer checkSensorExist(SensorNumber number);
        SensorPointer findSensor(SensorNumber number);

        template<typename CallbackIterate>
        void forEachSensor(CallbackIterate&& callback)
        {
            for (auto item : container_)
            {
                callback(item.first, item.second);
            }
        }
    private:
        std::map<SensorNumber, SensorPointer> container_;
    };

};

