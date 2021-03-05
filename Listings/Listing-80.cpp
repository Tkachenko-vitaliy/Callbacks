#include "Listing-79.h"

struct FOReturn
{
    int operator() (int eventID) { return 10; }
};

struct FOVoid
{
    void operator() (int eventID) {  /*do something*/ }
};

struct SResult
{
    unsigned int code;
    const char* description;
};

SResult ExternalReturn(int eventID)
{
    return SResult{ 1, "this is an error" };
}

void ExternalVoid(int eventID)
{
}

int main()
{
    int eventID = 0;

    FOReturn foRet;
    FOVoid   foVoid;

    auto lambdaRet = [](int eventID) { return 0.0; };
    auto lambdaVoid = [](int eventID) {};

    using FunPtrRet = SResult(*)(int);
    using LambdaTypeRet = decltype(lambdaRet);
    using FunPtrVoid = void(*)(int);
    using LambdaTypeVoid = decltype(lambdaVoid);

    StaticDistributor<FOReturn, FunPtrRet, LambdaTypeRet>  distributor1(foRet, ExternalReturn, lambdaRet);  // (1)
    StaticDistributor<FOVoid, FunPtrVoid, LambdaTypeVoid>  distributor2(foVoid, ExternalVoid, lambdaVoid);  // (2)

    auto results = distributor1(eventID);
    distributor2(eventID);
}
