#include "globals.h"

using namespace std;

map<int, Track*> g_tracks;
map<string, InOutTrack*> g_outTracks;
map<string, InOutTrack*> g_inTracks;
Dispatcher g_dispatcher("Dispatcher");
Histogram g_histTrackChanges("Zmeny kolaji dosledkom meskania vlakov", -1, 1, 10);
Histogram g_histWatingForOutput("Cakanie na uvolnenie odjazdovej kolaje", 0, 0.5, 15);
ofstream g_outputRealTimes;
ofstream g_outputChanges;
MyCalendar g_myCalendar;
