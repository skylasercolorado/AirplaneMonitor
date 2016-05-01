//
// Created by duncan on 5/1/16.
//

#ifndef AIRPLANEMONITOR_ANGULARSENSOR_HPP
#define AIRPLANEMONITOR_ANGULARSENSOR_HPP

#include "Sensor.hpp"

namespace Camax
{
    class AngularSensor : public sensor
    {
    public:
        AngularSensor(string name, Signal& source) : Sensor(name, source) {}

    protected:
        virtual string getUnits()
        {
            return "rad/s";
        }
    };
}
#endif //AIRPLANEMONITOR_ANGULARSENSOR_HPP
