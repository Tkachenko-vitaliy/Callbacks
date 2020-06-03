class EventCounter
{
public:
    void AddEvent(unsigned int event)
    {
        callCounter_++;
        lastEvent_ = event;
    }
private:
    unsigned int callCounter_ = 0;
    int lastEvent_ = 0;
};

class Executor
{
public:
    Executor(EventCounter* counter) : counter_(counter)
    {
        auto lambda = [this](int eventID)
        {
            //It will be called by initiator
            counter_->AddEvent(eventID);
            processEvent(eventID);
        };
        //Setup lambda in initiator
    }
private:
    EventCounter* counter_;
    void processEvent(int eventID) {/*Do something*/ }
};
