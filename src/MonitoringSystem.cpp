//
// Created by duncan on 5/7/16.
//

#include <algorithm>
#include "MonitoringSystem.hpp"

using namespace Camax;

void MonitoringSystem::TakeReading(Time t)
{
    for_each(sensors.begin(), sensors.end(),
             [&](Sensor* sensor)
             {
                 sensor->takeReading(t, recorder);
             });
}

