#include "ControlInterface.h"
#include "SensorControl.h"

using namespace sensor;

ISensorControl* ISensorControl::createControl()
{
    return new SensorControl;
}
