// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef _WINDOWS 
  #ifdef API_EXPORTS
    #define LIB_API __declspec(dllexport)
  #else
    #define LIB_API __declspec(dllimport)
  #endif
#else
  #define LIB_API
#endif

#include <stdint.h>

typedef uint32_t SensorNumber;
typedef double SensorValue;
typedef uint32_t CheckAlertTimeout;

typedef uint32_t SensorType;
typedef uint32_t DriverType;
typedef uint32_t AlertRule;

typedef void(*SensorValueCallback)(SensorNumber, SensorValue, void*);
typedef CheckAlertTimeout(*SensorAlertCallback)(SensorNumber, SensorValue, void*);
typedef SensorValue(*OnSimulateReadValue)(SensorNumber, int, void*);
typedef int (*OnSimulateOperable)(SensorNumber, void*);

enum eSensorType
{
    SENSOR_SPOT = 0,
    SENSOR_SMOOTH = 1,
    SENSOR_DERIVATIVE = 2,
};

enum eDriverType
{
    DRIVER_SIMULATION = 0,
    DRIVER_USB = 1,
    DRIVER_ETHERNET = 2
};

enum  eAlertRule
{
    ALERT_MORE = 0,
    ALERT_LESS = 1
};

typedef unsigned int ErrorCode;

LIB_API ErrorCode initialize();
LIB_API ErrorCode shutDown();
LIB_API ErrorCode assignDriver(DriverType type);
LIB_API ErrorCode getAssignedDriver(DriverType* type);
LIB_API ErrorCode getSensorDriver(SensorNumber number, DriverType* type);
LIB_API ErrorCode addSensor(SensorType type, SensorNumber number);
LIB_API ErrorCode deleteSensor(SensorNumber number);
LIB_API ErrorCode isSensorExist(SensorNumber number, int* isExist);
LIB_API ErrorCode isSensorOperable(SensorNumber number, int* isOperable);
LIB_API ErrorCode getSensorValue(SensorNumber number, SensorValue* value);
LIB_API ErrorCode querySensorValue(SensorNumber number, SensorValueCallback callback, void* pContextData);
LIB_API ErrorCode readSensorValues(SensorValueCallback callback, void* pContextData);
LIB_API ErrorCode getMinValue(SensorNumber first, SensorNumber last, SensorValue* value);
LIB_API ErrorCode getMaxValue(SensorNumber first, SensorNumber last, SensorValue* value);
LIB_API ErrorCode setAlert(SensorNumber number, SensorAlertCallback callback, SensorValue alertValue, AlertRule alertRule, CheckAlertTimeout checkTimeoutSet, void* pContextData);
LIB_API ErrorCode resetAlert(SensorNumber number);
LIB_API ErrorCode setSimulateReadCallback(OnSimulateReadValue callback, void* pContextData);
LIB_API ErrorCode setSimulateOperableCallback(OnSimulateOperable callback, void* pContextData);

enum eErrorCode
{
    ERROR_NO = 0,
    ERROR_NOT_INITIALIZED = 1,
    ERROR_UNKNOWN_TYPE = 2,
    ERROR_UNKNOWN_NUMBER = 3,
    ERROR_IS_NOT_OPERABLE = 4,
    ERROR_DRIVER_IS_NOT_SET = 5,
    ERROR_INVALID_ARGUMENT = 6,
    ERROR_NOT_SUPPORTED = 7,
    ERROR_INIT_DRIVER = 8
};
