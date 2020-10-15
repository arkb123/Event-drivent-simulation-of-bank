#include "Teller.h"
// all geters and seters are pretty stright forward
Teller::Teller(unsigned numOfTell)
{
    avaliable = false;
    numOFTellers = numOfTell;
    processedClients = 0;
    TransacationTime = 0;
    departureTime = 0;
    waitTime = 0;
}
bool Teller::isavaliable() const
{
    return avaliable;
}

void Teller::setavaliable(bool newavaliable)
{
    avaliable = newavaliable;
}

unsigned Teller::getNumberOfTellers() const
{
    return numOFTellers;
}

void Teller::setNumberOfTellers(unsigned num)
{
    numOFTellers = num;
}

double Teller::getProcessedClients() const
{
    return processedClients;
}

//keeps track and updates how many customers this teller has helped
void Teller::addClient()
{
    processedClients++;
}

double Teller::getTransactionTime() const
{
    return TransacationTime;
}

void Teller::addTT(double tt)
{
    TransacationTime += tt;
}

unsigned Teller::getDepartureTime() const
{
    return departureTime;
}

const Event &Teller::getCurrentEvent() const
{
    return currentEvent;
}

void Teller::setDT(unsigned dp)
{
    departureTime = dp;
}

void Teller::setCurrentEvent(const Event &currentEventt)
{
    currentEvent = currentEventt;
}

double Teller::getWaitTime() const
{
    return waitTime;
}

void Teller::addWaitTime(double waitTimee)
{
    waitTime += waitTimee;
}