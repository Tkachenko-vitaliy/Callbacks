#include "AlertControl.h"
#include "SensorInterface.h"

#include <chrono>

using namespace sensor;

void AlertControl::start()
{
    if (!pollThread_.joinable())
    {
        exit_ = false;
        pollThread_ = std::thread(&AlertControl::poll, this);
    }
}

void AlertControl::stop()
{
    if (pollThread_.joinable())
    {
        exit_ = true;
        pollThread_.join();
        containerAlert.clear();
    }
}

void AlertControl::poll()
{
    using namespace std::chrono_literals;

    while (!exit_)
    {
        std::this_thread::sleep_for(1s);
        std::lock_guard<std::mutex> lock(mutex_);

        for (auto& item : containerAlert)
        {
            Alert& alert = item.second;
            alert.currentTimeout++;
            if (alert.checkTimeout != 0 && alert.currentTimeout >= alert.checkTimeout)
            {
                bool triggerAlert = false;
                if (alert.alertRule == AlertRule::More)
                {
                    triggerAlert = alert.sensor->getValue() > alert.alertValue;
                }
                else
                {
                    triggerAlert = alert.sensor->getValue() < alert.alertValue;
                }
                if (triggerAlert)
                {
                    alert.checkTimeout = alert.callback(item.first, item.second.sensor->getValue());
                }
                alert.currentTimeout = 0;
            }
        }
    }
}

void AlertControl::addAlert(SensorNumber number, SensorPointer pointer, SensorAlertCallback callback, SensorValue alertValue, AlertRule alertRule, CheckAlertTimeout checkTimeoutSet)
{
    std::lock_guard<std::mutex> lock(mutex_);

    containerAlert[number] = Alert(callback, alertValue, alertRule, pointer, checkTimeoutSet);
}

void AlertControl::deleteAlert(SensorNumber number)
{
    std::lock_guard<std::mutex> lock(mutex_);

    containerAlert.erase(number);
}
