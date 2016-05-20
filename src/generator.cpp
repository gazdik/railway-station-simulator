#include "generator.h"

#include "globals.h"
#include "train.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

Generator::Generator(std::string fileName,
                     double delay, double delayProbability, double dayLength)
  : m_fileName{fileName}, m_delay{delay}, m_delayProbability{delayProbability},
    m_dayLength{dayLength}
{
  parseCSV();
}

Generator::~Generator()
{
//  g_tracks.clear();
//  g_outTracks.clear();
//  g_inTracks.clear();
}

void Generator::Behavior()
{
  double delay;

  for(trainParams &trainParams : m_timetable) {
    delay = 0;

    // Urci meskanie vlaku (na zaklade pravdepodobnosti, ci bude zmeskany
    // a exponencialnym rozlozenim
    if (Random() < m_delayProbability) {
      delay = Exponential(m_delay);
    }

    // Vlaky odchadzajuce z PU a neprechadzajuce zo ziadneho vlaku
    // nemaju meskanie
    if (trainParams.from == "PU")
      delay = 0;

    Train *train = new Train(trainParams);
    double time = (trunc(Time / m_dayLength) * m_dayLength)  + trainParams.arrival - trainParams.inTrack->seizeTime() + delay;

    train->Activate(time);

    // Add also to my calendar
    g_myCalendar.insert(train, time + trainParams.inTrack->seizeTime());
  }

  Activate(Time+ m_dayLength);
}
double Generator::getDelay() const
{
  return m_delay;
}

void Generator::setDelay(double value)
{
  m_delay = value;
}

double Generator::getDelayProbability() const
{
  return m_delayProbability;
}

void Generator::setDelayProbability(double value)
{
  m_delayProbability = value;
}

void Generator::parseCSV()
{
  ifstream ifs {m_fileName, ifstream::in};
  string line;
  istringstream line_stream;
  string token;
  trainParams trainRec;

  while(getline(ifs, line)) {
    line_stream.str(line);

    getline(line_stream, token, ',');
    trainRec.type = token;

    // IC trains doesn't need platform
    if (token == "IC") {
      trainRec.needPlatform = false;
    } else {
      trainRec.needPlatform = true;
    }

    getline(line_stream, token, ',');
    trainRec.number = stoi(token);

    getline(line_stream, token, ',');
    trainRec.arrival = stod(token);

    getline(line_stream, token, ',');
    trainRec.departure = stod(token);

    getline(line_stream, token, ',');
    trainRec.minWait = stod(token);

    getline(line_stream, token, ',');
    trainRec.track = g_tracks[stoi(token)];

    getline(line_stream, token, ',');
    trainRec.from = token;
    trainRec.inTrack = g_inTracks[token];

    getline(line_stream, token, ',');
    trainRec.to = token;
    trainRec.outTrack = g_outTracks[token];

    getline(line_stream, token, ',');
    if (token != "")
      trainRec.departureAsNumber = stoi(token);
    else
      trainRec.departureAsNumber = 0;

    getline(line_stream, token, ',');
    if (token != "")
      trainRec.waitForTrain = stoi(token);
    else
      trainRec.waitForTrain = 0;

    getline(line_stream, token, ',');
    if (token != "")
      trainRec.maxWaitTime = stoi(token);
    else
      trainRec.maxWaitTime = 0;


    m_timetable.push_back(trainRec);
  }
}
