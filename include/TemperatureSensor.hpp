//
// Created by duncan on 5/9/16.
//

#ifndef AIRPLANEMONITOR_TEMPERATURESENSOR_HPP
#define AIRPLANEMONITOR_TEMPERATURESENSOR_HPP

#include "Sensor.hpp"

namespace Camax
{
    class TemperatureSensor : public Sensor
    {
    public:
        TemperatureSensor(string name, Signal &source) : Sensor(name, source) {}

    protected:
        const string units = "Degrees Celsius";

        string getUnits()
        {
            return units;
        }
    };
}
#endif //AIRPLANEMONITOR_TEMPERATURESENSOR_HPP
