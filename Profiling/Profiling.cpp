#include <iostream>
#include <functional>

using namespace std;

#ifdef WIN32
    #define NO_INLINE _declspec (noinline)
#else
    #define NO_INLINE __attribute__ ((noinline))
#endif


//Comment the following line if you like to get standard (not built-in) code of Calculate function
#define BUILT_IN

#ifdef BUILT_IN
double Calculate(double input, int depth)
{
    double a1 = input, a2 = input + depth, multi = a2+depth;
    return ( (a1+multi) * a2) / ( (a2+multi) * a1);
}
#else
double Calculate(double input, int depth) //Recursive function will never be built-in
{
    if (depth == 0)
    {
        double a1 = input, a2 = input + depth, multi = a2 + depth;
        return ((a1 + multi) * a2) / ((a2 + multi) * a1);
    }
    else
    {
        double a1 = Calculate(input, depth - 1);
        double a2 = Calculate(input, depth - 1) + depth;
        double multi = a2 + depth;
        return ((a1 + multi) * a2) / ((a2 + multi) * a1);
    }
 }
#endif

class FO
{
public:
    double operator() (double val, int depth)
    {
        return Calculate(val, depth);
    }
};

double External(double val, int depth)
{
    return Calculate(val, depth);
}

class Calculator
{
public:
    virtual double calc(double val, int depth)
    {
        return Calculate(val,depth);
    }
};

std::function<double(double, int)> g_function;
std::function<double(Calculator*, double, int)> g_functionClass;

using ptr_function = double(*)(double,int);
using ptr_method = double(Calculator::*)(double,int);

FO    g_fo;
Calculator g_calc;
ptr_function g_PointerExternal = nullptr;
ptr_method g_PointerMethod = nullptr;

NO_INLINE double call_Pointer(unsigned int count, int offset, int depth)
{
    double check = offset;

    for (size_t i = 0; i < count; i++)
    {
        check += g_PointerExternal(check, depth);
    }
   
    return check;
}



NO_INLINE double call_Object(unsigned int count, int offset, int depth)
{
    double check = offset;
   
    for (size_t i = 0; i < count; i++)
    {
        check += g_fo(check,depth);
    }

     return check;
}


NO_INLINE double call_Method(unsigned int count, int offset, int depth)
{
    double check = offset;

    for (size_t i = 0; i < count; i++)
    {
        check += (g_calc.*g_PointerMethod)(check, depth);
    }
    return check;
}

NO_INLINE double call_Lambda(unsigned int count, int offset, int depth)
{
    double check = offset;

    auto lambda = [](double val, int depth) {return Calculate(val, depth); };

    for (size_t i = 0; i < count; i++)
    {
        check += lambda(check,depth);
    }

    return check;
}

NO_INLINE double call_Pointer_f(unsigned int count, int offset, int depth)
{
    double check = offset;

    for (size_t i = 0; i < count; i++)
    {
        check += g_function(check, depth);
    }
    return check;
}

NO_INLINE double call_Object_f(unsigned int count, int offset, int depth)
{
    double check = offset;

    for (size_t i = 0; i < count; i++)
    {
        check += g_function(check, depth);
    }
    return check;
}

NO_INLINE double call_Method_f(unsigned int count, int offset, int depth)
{
    double check = offset;

    for (size_t i = 0; i < count; i++)
    {
        check += g_functionClass(&g_calc, check, depth);
    }
    return check;
}

NO_INLINE double call_Lambda_f(unsigned int count, int offset, int depth)
{
    double check = offset;

    for (size_t i = 0; i < count; i++)
    {
        check += g_function(check,depth);
    }
    return check;
}



int main()
{
    unsigned int count = 1000000;
    double result = 0; int offset = 1; int depth = 2;

    g_PointerExternal = Calculate;
    g_PointerMethod = &Calculator::calc;

    offset++;
    result = call_Pointer(count, offset, depth);
    cout << result << endl;

    offset++;
    result = call_Object(count, offset, depth);
    cout << result << endl;

    offset++;
    result = call_Method(count, offset, depth);
    cout << result << endl;
    
    offset++;
    result = call_Lambda(count, offset, depth);
    cout << result << endl;
    
    offset++;
    g_function = External; 
    result = call_Pointer_f(count, offset, depth);
    cout << result << endl;
    
    offset++;
    g_function = g_fo; 
    result = call_Object_f(count, offset, depth);
    cout << result << endl;

    offset++;
    g_functionClass = std::mem_fn(&Calculator::calc); 
    result = call_Method_f(count, offset, depth);
    cout << result << endl;

    offset++;
    auto lambda = [](double val, int depth) {return Calculate(val, depth); };
    g_function = lambda; 
    result = call_Lambda_f(count, offset, depth);
    cout << result << endl;
}
