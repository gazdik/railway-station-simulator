#include <simlib.h>

#include "globals.h"
#include "generator.h"
#include <iostream>

using namespace std;

const double PR_OUTWAIT = 2.38;
const double KE_OUTWAIT = 1;
const double BA_OUTWAIT = 2.53;
const double PR_INWAIT= 1;
const double KE_INWAIT = 1;
const double BA_INWAIT = 1;

const double DAY_LENGTH = 1440;

void initSimulation(const char *outRealtimes, const char *outChanges, const char *outStatistics)
{
  SetOutput(outStatistics);
  g_outputRealTimes.open(outRealtimes, ofstream::out);
  g_outputChanges.open(outChanges, ofstream::out);

  g_tracks[1] = (new Track("Track_1", 1, 'U', false));
  g_tracks[2] = (new Track("Track_2", 2, 'D', false));
  g_tracks[3] = (new Track("Track_3", 3, 'U', true));
  g_tracks[4] = (new Track("Track_4", 4, 'D', true));
  g_tracks[7] = (new Track("Track_7", 7, 'U', true));
  g_tracks[8] = (new Track("Track_8", 8, 'D', true));

  g_outTracks["PR"] = (new InOutTrack{"Kolaj do Prahy", PR_OUTWAIT});
  g_outTracks["BA"] = (new InOutTrack{"Kolaj do Bratislavy", BA_OUTWAIT});
  g_outTracks["KE"] = (new InOutTrack{"Kolaj do Kosic", KE_OUTWAIT});

  g_outTracks["PU"] = (new InOutTrack{"Odstavne kolaje", 0});

  g_inTracks["PR"] = (new InOutTrack{"Kolaj z Prahy", PR_INWAIT});
  g_inTracks["BA"] = (new InOutTrack{"Kolaj z Bratislavy", BA_INWAIT});
  g_inTracks["KE"] = (new InOutTrack{"Kolaj z Kosic", KE_INWAIT});
  g_inTracks["PU"] = (new InOutTrack{"Pristavenie z odstavnej kolaje", 0});
}

void outputStat()
{
  g_tracks[1]->Output();
  g_tracks[2]->Output();
  g_tracks[3]->Output();
  g_tracks[4]->Output();
  g_tracks[7]->Output();
  g_tracks[8]->Output();

  g_outTracks["BA"]->Output();
  g_outTracks["KE"]->Output();
  g_outTracks["PU"]->Output();
  g_outTracks["PR"]->Output();

  g_inTracks["BA"]->Output();
  g_inTracks["KE"]->Output();
  g_inTracks["PU"]->Output();
  g_inTracks["PR"]->Output();

  g_dispatcher.Output();
  g_histTrackChanges.Output();
  g_histWatingForOutput.Output();
}

void closeSimulation()
{

  g_outputChanges.close();
  g_outputRealTimes.close();

  for (auto &i : g_tracks) {
    i.second->Clear();
    delete i.second;
  }

  for (auto &i : g_outTracks) {
    i.second->Clear();
    delete i.second;
  }

  for (auto &i : g_inTracks) {
    i.second->Clear();
    delete i.second;
  }

  g_dispatcher.Clear();
  g_histTrackChanges.Clear();
  g_histWatingForOutput.Clear();
  g_histTrackChanges.Init(-1, 1, 10);
  g_histWatingForOutput.Init(0, 0.5, 15);
  g_myCalendar.clear();
}

int main()
{
  RandomSeed(time(NULL));

  /*
   * Experiment č.1
   * bez meskania
   */
  Init(0, DAY_LENGTH*100);
  initSimulation("exp1_realtimes.txt", "exp1_trackChanges.txt", "exp1_statistics.txt");
  (new Generator("timetable/ex124.csv", 0, 0))->Activate();
  Run();
  outputStat();
  closeSimulation();

//  /*
//   * Experiment č.2
//   * s priemernym meskanim
//   */
  Init(0, DAY_LENGTH*100);
  initSimulation("exp2_realtimes.txt", "exp2_trackChanges.txt", "exp2_statistics.txt");
  (new Generator("timetable/ex124.csv", 11.96, 0.2023))->Activate();
  Run();
  outputStat();
  closeSimulation();

  /*
   * Experiment č.3
   * v spicke od 14:00 do 17:00
   */
  Init(0, 180*100);
  initSimulation("exp3_realtimes.txt", "exp3_trackChanges.txt", "exp3_statistics.txt");
  (new Generator("timetable/ex3.csv", 11.93, 0.2023))->Activate();
  Run();
  outputStat();
  closeSimulation();

  /*
   * Experiment č.4
   * s velkymi meskaniami
   */
//  initSimulation("exp4_realtimes.txt", "exp4_trackChanges.txt", "exp4_statistics.txt");
//  Init(0, 180*100);
//  (new Generator("timetable/ex124.csv", 45, 0.5))->Activate();
//  Run();
//  outputStat();
//  closeSimulation();



  return 0;
}

