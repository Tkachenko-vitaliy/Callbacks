#pragma once

#include "SensorDef.h"

#include <queue>
#include <condition_variable>
#include <thread>

namespace sensor
{

    class CommandQueue
    {
    public:
        void start();
        void stop();
        void addCommand(SensorNumber number, SensorPointer pointer, SensorValueCallback callback);

    private:
        struct Command
        {
            SensorNumber number;
            SensorPointer pointer;
            SensorValueCallback callback;
        };
        std::queue<Command> commandQueue_;
        std::condition_variable conditional_;
        std::mutex mutex_;
        std::thread queueThread_;
        bool exit_;

        void readCommand();
    };

}; //namespace sensor