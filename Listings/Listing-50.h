#pragma once

//General specialization
template <typename ClassName, typename unused>  // (1)
class CallbackToClass;

//Partial specialization
template<typename ClassName, typename Return, typename ... ArgumentList>  // (2)
class CallbackToClass<ClassName, Return(ArgumentList...)>
{
public:
    using ClassMethod = void(ClassName::*)(ArgumentList...); // (3) 

    CallbackToClass(ClassName* classPointer = nullptr, ClassMethod methodPointer = nullptr)  // (4) 
    {
        ptrClass = classPointer; ptrMethod = methodPointer;
    }

    Return operator()(ArgumentList... arguments)  // (5)
    {
        (ptrClass->*ptrMethod)(arguments...);  // (6) 
    }
private:
    ClassName* ptrClass;  // (7)
    ClassMethod ptrMethod;  // (8)
};

