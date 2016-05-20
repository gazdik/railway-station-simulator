#include "inouttrack.h"

InOutTrack::InOutTrack(const char *name, double seizeTime)
  : Facility {name}, m_seizeTime {seizeTime}
{
}
double InOutTrack::seizeTime() const
{
  return m_seizeTime;
}

void InOutTrack::setSeizeTime(double seizeTime)
{
  m_seizeTime = seizeTime;
}

