#include "track.h"

Track::Track(const char *name, int number, char defaultSide, bool hasPlatform)
  : Facility {name}, m_number {number},
    m_defaultDir {defaultSide}, m_hasPlatform {hasPlatform}
{

}

bool Track::hasPlatform() const
{
  return m_hasPlatform;
}
int Track::number() const
{
  return m_number;
}

void Track::setNumber(int number)
{
  m_number = number;
}
char Track::defaultDir() const
{
  return m_defaultDir;
}

void Track::setDefaultDir(char defaultDir)
{
  m_defaultDir = defaultDir;
}


