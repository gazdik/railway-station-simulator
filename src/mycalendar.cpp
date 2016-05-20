#include "mycalendar.h"

#include <algorithm>

using namespace std;

bool compEvent (MyEvent *event, double time) {return event->time < time; }

MyCalendar::MyCalendar()
{
}

void MyCalendar::insert(Train *train, double time)
{
  EventList::iterator insertPos;

  MyEvent tmp;
  tmp.time = time;

//  insertPos = lower_bound(m_events.begin(), m_events.end(), time, compEvent);
  insertPos = lower_bound(m_events.begin(), m_events.end(), tmp);

  MyEvent event;
  event.train = train;
  event.time = time;

  m_events.insert(insertPos, event);
}

void MyCalendar::remove(Train *train)
{
  MyEvent tmp;
  tmp.train = train;

  m_events.remove(tmp);
}

void MyCalendar::clear()
{
  m_events.clear();
}
