#pragma once

class Executor
{
public:
    virtual void callbackHandler1(int eventID);
    virtual void callbackHandler2(int eventID);
};

class Executor1 : public Executor
{
public:
    void callbackHandler1(int eventID) override;
};

class Executor2 : public Executor
{
public:
    void callbackHandler2(int eventID) override;
};

class Executor3 : public Executor1, public Executor2
{

};

