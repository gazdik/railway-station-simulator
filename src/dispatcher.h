#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <simlib.h>
#include "train.h"

class Dispatcher : public Facility
{
public:
  Dispatcher();
  Dispatcher(const char* name) : Facility {name} {}
  void getTrack(Train &train);

private:
};

#endif // DISPATCHER_H
