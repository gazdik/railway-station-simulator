#ifndef GENERATOR_H
#define GENERATOR_H

#include "track.h"
#include "train.h"

#include <simlib.h>
#include <string>
#include <vector>


class Generator : public Event
{
public:
  Generator(std::string m_fileName, double m_delay, double m_delayProbability, double dayLength = 1440);

  Generator();
  ~Generator();
  void Behavior();

  double getDelay() const;
  void setDelay(double value);

  double getDelayProbability() const;
  void setDelayProbability(double value);

private:
  void parseCSV();

  std::string m_fileName;
  double m_delay;
  double m_delayProbability;
  double m_dayLength;

  std::vector<trainParams> m_timetable;
};


#endif // GENERATOR_H
