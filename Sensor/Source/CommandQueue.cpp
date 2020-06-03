#include "CommandQueue.h"
#include "SensorInterface.h"

using namespace sensor;

void CommandQueue::start()
{
    if (!queueThread_.joinable())
    {
        exit_ = false;
        queueThread_ = std::thread(&CommandQueue::readCommand, this);
    }
}

void CommandQueue::stop()
{
    if (queueThread_.joinable())
    {
        std::unique_lock<std::mutex> lock(mutex_);
        exit_ = true;
        lock.unlock();
        conditional_.notify_one();
        queueThread_.join();
        commandQueue_ = decltype(commandQueue_)();
    }
}

void CommandQueue::addCommand(SensorNumber number, SensorPointer pointer, SensorValueCallback callback)
{
    std::lock_guard<std::mutex> lock(mutex_);

    commandQueue_.push({ number, pointer, callback });

    conditional_.notify_one();
}

void CommandQueue::readCommand()
{
    while (!exit_)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        conditional_.wait(lock, [this]() {return commandQueue_.size() > 0 || exit_ == true; });

        while (commandQueue_.size() > 0 && exit_ == false)
        {
            Command cmd = commandQueue_.front();
            commandQueue_.pop();
            lock.unlock();
            cmd.callback(cmd.number, cmd.pointer->getValue());
            lock.lock();
        }
    }
}