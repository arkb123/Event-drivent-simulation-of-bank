#ifndef TELLERH
#define TELLERH

#include "Event.h"
class Teller
{
private:
    bool avaliable;
    unsigned numOFTellers;
    double processedClients, TransacationTime, waitTime;
    unsigned departureTime;
    Event currentEvent;

public:
    const Event &getCurrentEvent() const;
    void setCurrentEvent(const Event &currentEventt);
    Teller(unsigned numOfTellers);
    double getTransactionTime() const;
    unsigned getDepartureTime() const;
    double getWaitTime() const;
    void addWaitTime(double waitTimee);
    bool isavaliable() const;
    unsigned getNumberOfTellers() const;
    void setavaliable(bool newavaliable);
    void setNumberOfTellers(unsigned num);
    void setDT(unsigned dp);
    void addClient();
    void addTT(double tt);
    double getProcessedClients() const;
};
#endif