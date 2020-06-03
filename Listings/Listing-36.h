#pragma once

class Executor;

class CallbackHandler
{
public:
    void operator() (int eventID);
};

//Pointer to function
class Initiator1
{
public:
    using ptr_callback = void(*) (int, void*);

    void setup(ptr_callback pPtrCallback, void* pContextData);

private:
    ptr_callback ptrCallback = nullptr;
    void* contextData = nullptr;
};

//Pointer to the class static method
class Initiator2
{
public:
    using ptr_callback_static = void(*) (int, Executor*);

    void setup(ptr_callback_static pPtrCallback, Executor* pContextData);

private:
    ptr_callback_static ptrCallback = nullptr;
    Executor* contextData = nullptr;
};

//Pointer to the class member method
class Initiator3
{
public:
    using ptr_callback_method = void(Executor::*)(int);

    void setup(Executor* argCallbackClass, ptr_ callback_method argCallbackMethod);

private:
    Executor* ptrCallbackClass = nullptr;
    ptr_ callback_method ptrCallbackMethod = nullptr;
};

//Functional object
class Initiator4
{
public:
    void setup(const CallbackHandler& callback);

private:
    CallbackHandler callbackObject;
};

