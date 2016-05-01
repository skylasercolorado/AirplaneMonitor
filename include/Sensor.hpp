//
// Created by duncan on 5/1/16.
//

#ifndef AIRPLANEMONITOR_SENSOR_HPP
#define AIRPLANEMONITOR_SENSOR_HPP

#include "Signal.hpp"
#include "DataRecorder.hpp"

namespace Camax
{
    class Sensor
    {
    public:
        Sensor(string name, Signal &source) : name(name), source(source) {}
        virtual ~Sensor() {}
        void takeReading(Time t, IDataRecorder &recorder)
        {
            recorder.log(t, name, source.getVoltageAtTime(t), this->getUnits());
        }

    protected:
        virtual string getUnits() = 0;
        string getName() { return name; }
        Signal &getSource() { return source; }

    private:
        string name;
        Signal &source;
    };
}

#endif //AIRPLANEMONITOR_SENSOR_HPP
