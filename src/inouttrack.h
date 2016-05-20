#ifndef INOUTTRACK_H
#define INOUTTRACK_H

#include <simlib.h>

class InOutTrack : public Facility
{
public:
  InOutTrack(const char* name, double seizeTime);

  double seizeTime() const;
  void setSeizeTime(double seizeTime);

private:
  double m_seizeTime;
};

#endif // INOUTTRACK_H
