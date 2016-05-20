#ifndef TRAIN_H
#define TRAIN_H

#include <simlib.h>
#include "track.h"
#include "inouttrack.h"

#include <string>
#include <fstream>

struct trainParams {
  std::string type;
  int number;
  double arrival;
  double departure;
  Track* track;
  std::string from;
  InOutTrack* inTrack;
  std::string to;
  InOutTrack* outTrack;
  int departureAsNumber;
  double minWait;
  int waitForTrain;
  double maxWaitTime;
  bool needPlatform;
};

class Train : public Process
{
public:
  Train(trainParams &parameters);

  void Behavior();

  void OutputRealTimes();

  // Getters and setters
  std::string getType() const;
  void setType(const std::string &value);
  int getNumber() const;
  void setNumber(int value);
  double getArrival() const;
  void setArrival(double value);
  double getDeparture() const;
  void setDeparture(double value);
  std::string getFrom() const;
  void setFrom(const std::string &value);
  Track *getTrack() const;
  void setTrack(Track *value);
  bool needPlatform() const;
  void setNeedPlatform(bool needPlatform);
  double minWait() const;
  void setMinWait(double minWait);
  bool trackChanged() const;
  void setTrackChanged(bool trackChanged);
  std::string to() const;
  void setTo(const std::string &to);

  void changeName(int number);

  InOutTrack *inTrack() const;
  void setInTrack(InOutTrack *inTrack);

  InOutTrack *outTrack() const;
  void setOutTrack(InOutTrack *outTrack);

public:
  // Type of train - R, Os, IC, Ex
  std::string m_type;
  // Train number
  int m_number;
  // Time of arrival
  double m_arrival;
  // Time of departure
  double m_departure;
  // Reserved track
  Track *m_track;
  // Arrived from
  std::string m_from;
  // Input track
  InOutTrack *m_inTrack;
  // Smer odjazdu vlaku
  std::string m_to;
  // Output track from station
  InOutTrack *m_outTrack;
  // Vlak odchadza pod inym cislom
  int m_departureAsNumber;
  // Does train need platform?
  bool m_needPlatform;
  // Minimal time for boarding
  double m_minWait;
  // Cakanie na vlak pripojny vlak cislo
  int m_waitForTrain;
  // Maximalna doba cakania na pripojny vlak
  double m_maxWaitTime;


  // Doba cakania v stanici pridelena od discpera
  double m_wait;
  // Cas skutocneho odjazdu
  double m_realDeparture;
  // Cas skutocneho prijazdu
  double m_realArrival;
  // Ak doslo k zmene kolaje
  bool m_trackChanged = false;
  // Meno vlaku (procesu)
  char m_name[8];
};

#endif // TRAIN_H
