//
// Created by duncan on 5/7/16.
//

#ifndef AIRPLANEMONITOR_PRESSURESENSOR_HPP
#define AIRPLANEMONITOR_PRESSURESENSOR_HPP

#include "Sensor.hpp"

namespace Camax
{
    class PressureSensor : public Sensor
    {
    public:
       PressureSensor(string name, Signal &source) : Sensor(name, source) {}

    protected:
        string getUnits()
        {
            return "Pounds per square inch (PSI)";
        }
    };
}
#endif //AIRPLANEMONITOR_PRESSURESENSOR_HPP
