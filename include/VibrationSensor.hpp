//
// Created by duncan on 5/9/16.
//

#ifndef AIRPLANEMONITOR_VIBRATIONSENSOR_HPP
#define AIRPLANEMONITOR_VIBRATIONSENSOR_HPP

#include "Sensor.hpp"

namespace Camax
{
    class VibrationSensor : public Sensor
    {
    public:
        VibrationSensor(string name, Signal &source) : Sensor(name, source) {}

    protected:
        const string units = "Hertz (Hz)";

        string getUnits()
        {
            return units;
        }
    };
}
#endif //AIRPLANEMONITOR_VIBRATIONSENSOR_HPP
