#include "dispatcher.h"

#include "globals.h"
#include <iostream>

using namespace std;

#define UNREACHABLE 100
#define BUSY 100
#define DIFFERENT_DIR 10
#define CHANGE_TIME 3

Dispatcher::Dispatcher()
{
}

void Dispatcher::getTrack(Train &train)
{

  // Urci cas cakania vlaku v stanici:
  train.m_wait = (train.m_departure - Time < train.m_minWait)
      ? train.m_minWait : (train.m_departure - Time);


  // Ak vlak caka na pripoj, zisti, ci ma cenu na neho cakat,
  // t.j. ci uz prisiel alebo pride az za cas, kedy sa na neho neoplati cakat
  if (train.m_waitForTrain != 0) {
    for (MyEvent &event : g_myCalendar) {

      // Ukonci hladanie, ak to uz nema cenu
      if (event.time > train.m_departure + train.m_maxWaitTime)
        break;

      // Urci dobu cakania na pripojny vlak
      if (event.train->m_number == train.m_waitForTrain) {
        if (train.m_departure - event.time < CHANGE_TIME) {
          train.m_wait = (event.time + CHANGE_TIME) - Time;
        }
      }
    }
  }


  // Ak je rezervovana kolaj pre vlak obsadena, najdi dalsiu najvhodnejsiu
  if (train.getTrack()->Busy()) {
    Track *chosenTrack = train.getTrack();
    int bestScore = UNREACHABLE;

    // Vypocitaj hodnotiacu funkciu pre kazdu kolaj a zvol tak najvhodnejsiu
    for (auto &i : g_tracks) {
      Track *currTrack = i.second;
      int score = 0;

      if (train.needPlatform() && !currTrack->hasPlatform())
        score += UNREACHABLE;

      if (currTrack->Busy()) {
        score += BUSY;
      }

      if ((train.to() == "KE" && currTrack->defaultDir() == 'D')
          || ((train.to() == "PR" || train.to() == "BA") && currTrack->defaultDir() == 'U'))
        score += DIFFERENT_DIR;

      for (MyEvent &event : g_myCalendar) {
        double departure = train.m_wait + Time;
        if (event.time  > departure)
          break;

        if (event.train->getTrack() == currTrack)
          score += BUSY;
      }

      if (score < bestScore) {
        bestScore = score;
        chosenTrack = currTrack;
      }
    }

    // Vypis zmenu kolaje do suboru
    g_outputChanges << train.getTrack()->Name() << " " << chosenTrack->Name()
                       << " " << train.Name() << " "
                       << train.getTrack()->in->Name() << endl;

    g_histTrackChanges(train.getTrack()->number());
    train.setTrack(chosenTrack);
    train.setTrackChanged(true);
  } else {
    // Ak nedoslo k zmene kolaje, uved to do histogramu ako hodnotu -1
    g_histTrackChanges(-1);
  }
}

