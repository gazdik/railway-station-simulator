#include "train.h"

#include "globals.h"
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

Train::Train(trainParams &parameters)
  : m_type{parameters.type}, m_number{parameters.number},
    m_track{parameters.track}, m_from{parameters.from},
    m_inTrack{parameters.inTrack}, m_to{parameters.to},
    m_outTrack{parameters.outTrack},
    m_departureAsNumber{parameters.departureAsNumber},
    m_needPlatform{parameters.needPlatform}, m_minWait{parameters.minWait},
    m_waitForTrain{parameters.waitForTrain}, m_maxWaitTime{parameters.maxWaitTime},
    m_wait{0}
{
  m_arrival = parameters.arrival + Time;
  m_departure = parameters.departure + Time;
  sprintf(m_name, "%d", m_number);
  SetName(m_name);
}

void Train::Behavior()
{
  // Seize input track to station
  Seize(*m_inTrack);
  Wait(m_inTrack->seizeTime());
  Release(*m_inTrack);

  // Ziskaj cislo kolaje a dobu cakania v stanici od dispecera
  Seize(g_dispatcher);
  g_dispatcher.getTrack(*this);
  Release(g_dispatcher);

  // Vojdi na kolaj v stanici pridelenu od dispecera
  Seize(*m_track);
  // Odstran udalost z vlastneho kalendara
  g_myCalendar.remove(this);

  // Ulozenie skutocneho casu prijazdu
  m_realArrival = Time;

  // Pockaj do casu odchodu, pripadne minimalny cas potrebny pre odbavenie vlaku
  Wait(m_wait);

  // Ak odchadzas ako iny spoj, zmen meno
  if (m_departureAsNumber != 0) {
    changeName(m_departureAsNumber);
  }

  // Zaber si odchodziu kolaj a uvolni kolaj a uvolni kolaj v stanici
  double waitBegin = Time;
  Seize(*m_outTrack);

  // Statistika cakania na odchodziu kolaj
  if (Time != waitBegin)
    g_histWatingForOutput(Time - waitBegin);

  Release(*m_track);

  // Ulozenie skutocneho casu odjazdu
  m_realDeparture = Time;

  Wait(m_outTrack->seizeTime());
  Release(*m_outTrack);

  // Vypis do suboru skutocny cas prijazdu a odjazdu
  OutputRealTimes();
}

void Train::OutputRealTimes()
{
  string track;
  if (m_trackChanged)
    track = "Changed_track";
  else
    track = "Reserved_track";

  g_outputRealTimes << m_track->Name()
                    << "\t" << m_realArrival
                    << "\t" << m_realDeparture
                    << "\t" << track
                    << "\t" << Name() << endl;
}

Track *Train::getTrack() const
{
  return m_track;
}

void Train::setTrack(Track *value)
{
  m_track = value;
}
bool Train::needPlatform() const
{
  return m_needPlatform;
}

void Train::setNeedPlatform(bool needPlatform)
{
  m_needPlatform = needPlatform;
}
double Train::minWait() const
{
  return m_minWait;
}

void Train::setMinWait(double minWait)
{
  m_minWait = minWait;
}
bool Train::trackChanged() const
{
  return m_trackChanged;
}

void Train::setTrackChanged(bool trackChanged)
{
  m_trackChanged = trackChanged;
}
std::string Train::to() const
{
  return m_to;
}

void Train::setTo(const std::string &to)
{
  m_to = to;
}

void Train::changeName(int number)
{
  sprintf(m_name, "%d", number);
}
InOutTrack *Train::inTrack() const
{
  return m_inTrack;
}

void Train::setInTrack(InOutTrack *inTrack)
{
  m_inTrack = inTrack;
}
InOutTrack *Train::outTrack() const
{
  return m_outTrack;
}

void Train::setOutTrack(InOutTrack *outTrack)
{
  m_outTrack = outTrack;
}

std::string Train::getFrom() const
{
  return m_from;
}

void Train::setFrom(const std::string &value)
{
  m_from = value;
}

double Train::getDeparture() const
{
  return m_departure;
}

void Train::setDeparture(double value)
{
  m_departure = value;
}

double Train::getArrival() const
{
  return m_arrival;
}

void Train::setArrival(double value)
{
  m_arrival = value;
}

int Train::getNumber() const
{
  return m_number;
}

void Train::setNumber(int value)
{
  m_number = value;
}

std::string Train::getType() const
{
  return m_type;
}

void Train::setType(const std::string &value)
{
  m_type = value;
}

