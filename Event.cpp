// Event.cpp

#include "Event.h"

// IMPLEMENT ALL THE Event OPERATIONS HERE

Event::Event()
{
    eType = undefined;
    eTime = 0;
    eDuration = 0;
    placeInQue = 0;
}
Event::Event(eventType type, unsigned time, unsigned duration)
{
    eType = type;
    eTime = time;
    eDuration = duration;
}
Event::Event(const Event &otherEvent)
{

    eType = otherEvent.getType();
    eDuration = otherEvent.getDuration();
    eTime = otherEvent.getTime();
    placeInQue = otherEvent.getPlaceinQue();
}

//Determines the type of the event
Event::eventType Event::getType() const
{
    return eType;
}

// Determines the time of the event
unsigned Event::getTime() const
{
    return eTime;
}

// Determines the duration of the (arrival) event
unsigned Event::getDuration() const
{
    return eDuration;
}

unsigned Event::getPlaceinQue() const
{
    return placeInQue;
}
//sets event type
void Event::setType(Event::eventType eTypee)
{
    eType = eTypee;
}
//sets time
void Event::setTime(unsigned eTimee)
{
    eTime = eTimee;
}
//sets duration 
void Event::setDuration(unsigned eDurationn)
{
    eDuration = eDurationn;
}

unsigned Event::gettellerNum() const
{
    return tellerNum;
}

void Event::settellerNum(unsigned newNumm)
{
    tellerNum = newNumm;
}

// Events are ordered by their event time (occurance)
// had to had a new condtion if they were equal
bool operator<(const Event &lhs, const Event &rhs)
{
    if (lhs.getTime() == rhs.getTime() && !(lhs.getType() == rhs.getType())){                                              
        return (lhs.getType() == Event::departure);
    }
    else if ((lhs.getType() == Event::departure && rhs.getType() == Event::departure) && (lhs.getTime() == rhs.getTime())){ 
        return (lhs.gettellerNum() < rhs.gettellerNum());
    }
    else{
        return (lhs.getTime() < rhs.getTime()); 
    }
}
bool operator>(const Event &lhs, const Event &rhs)
{
    return ((rhs < lhs));
}