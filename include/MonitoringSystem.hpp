//
// Created by duncan on 5/7/16.
//

#ifndef AIRPLANEMONITOR_MONITORINGSYSTEM_HPP
#define AIRPLANEMONITOR_MONITORINGSYSTEM_HPP

#include <vector>
#include "DataRecorder.hpp"
#include "Sensor.hpp"

namespace Camax
{
    class MonitoringSystem
    {
    public:
        MonitoringSystem(ostream &out) : recorder(out) {}
        void AddSensor(Sensor *sensor)
        {
            sensors.push_back(sensor);
        }
        void TakeReading(Time t);

    private:
        DataRecorder recorder;
        std::vector<Sensor *> sensors;
    };
}

#endif //AIRPLANEMONITOR_MONITORINGSYSTEM_HPP
