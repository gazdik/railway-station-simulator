#ifndef GLOBALS_H
#define GLOBALS_H

#include "track.h"
#include "inouttrack.h"
#include "dispatcher.h"
#include "mycalendar.h"
#include <map>
#include <string>
#include <fstream>

// Facilities
extern std::map<int, Track*> g_tracks;
extern std::map<std::string, InOutTrack*> g_outTracks;
extern std::map<std::string, InOutTrack*> g_inTracks;
extern Dispatcher g_dispatcher;

// Vlastny kalendar
extern MyCalendar g_myCalendar;

// Statistiky
extern Histogram g_histTrackChanges;
extern Histogram g_histWatingForOutput;
extern std::ofstream g_outputRealTimes;
extern std::ofstream g_outputChanges;



#endif // GLOBALS_H
