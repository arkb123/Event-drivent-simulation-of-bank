#ifndef EVENT_H_
#define EVENT_H_

class Event
{

public:
  enum eventType
  {
    undefined,
    arrival,
    departure
  };

  Event();
  Event(eventType type, unsigned time, unsigned duration = 0);
  Event(const Event &otherEvent);

  // Determines the type of the event
  eventType getType() const;

  // Determines the time of the event. When it took place. Used for que.
  unsigned getTime() const;

  // Determines the duration of the (arrival) event
  unsigned getDuration() const;

   // same as last prog
  friend bool operator<(const Event &lhs, const Event &rhs);
  friend bool operator>(const Event &lhs, const Event &rhs);
  //added another bool aperator
  friend bool operator==(const Event &lhs, const Event &rhs);

  unsigned getPlaceinQue() const;
  void setPlaceinQue() const;
  void setType(eventType eTypee);
  void setTime(unsigned eTimee);
  void setDuration(unsigned eDurationn);
  unsigned getNumberofTellers() const;
  void settellerNum(unsigned newNumm);
  unsigned gettellerNum() const;

private:
  eventType eType;    // type of event
  unsigned eTime;     // time of event occurance
  unsigned eDuration; // duration, if event is an arrival event
  unsigned placeInQue;
  unsigned tellerNum;
};

#endif