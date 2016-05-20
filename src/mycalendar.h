#ifndef MYCALENDAR_H
#define MYCALENDAR_H

#include "train.h"
#include <list>

struct MyEvent {
  double time;
  Train *train;

  friend bool operator == (const MyEvent& lhs, const MyEvent& rhs)
  {
    return lhs.train->getNumber() == rhs.train->getNumber();
  }

  friend bool operator < (const MyEvent& lhs, const MyEvent& rhs)
  {
    return lhs.time < rhs.time;
  }
};


class MyCalendar
{
public:
  MyCalendar();
  void insert(Train *train, double time);
  void remove(Train* train);
  void clear();

private:
  typedef std::list<MyEvent> EventList;
  EventList m_events;

public:
  typedef EventList::iterator iterator;
  typedef EventList::const_iterator const_iterator;
  iterator begin() { return m_events.begin(); }
  iterator end() { return m_events.end(); }
};

#endif // MYCALENDAR_H
