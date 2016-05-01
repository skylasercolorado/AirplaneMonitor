//
// Created by duncan on 4/30/16.
//

#ifndef AIRPLANEMONITOR_SINESIGNAL_HPP
#define AIRPLANEMONITOR_SINESIGNAL_HPP

#include "PeriodicSignal.hpp"

using namespace Camax;

class SineSignal : public PeriodicSignal
{
public:
    SineSignal(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period)
            : PeriodicSignal(voltageOffset, timeOffset, minVoltage, maxVoltage, period) {}

    double getVoltageAtTime(Time t)
    {

    }
};
#endif //AIRPLANEMONITOR_SINESIGNAL_HPP
