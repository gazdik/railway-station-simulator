#ifndef TRACK_H
#define TRACK_H

#include <simlib.h>

class Track : public Facility
{
public:
  Track(const char* name, int number, char defaultSide, bool hasPlatform);

  bool hasPlatform() const;

  int number() const;
  void setNumber(int number);

  char defaultDir() const;
  void setDefaultDir(char defaultDir);

private:
  int m_number;
  // Default for trains going to UP or DOWN
  // 'U' = UP = Trains to Kosice
  // 'D' = Trains to Bratislava nad Prague
  char m_defaultDir;
  bool m_hasPlatform;
};

#endif // TRACK_H
