//
// Created by duncan on 4/30/16.
//

#ifndef AIRPLANEMONITOR_PERIODICSIGNAL_HPP
#define AIRPLANEMONITOR_PERIODICSIGNAL_HPP

#include "Signal.hpp"

using namespace Camax;

class PeriodicSignal : public Signal
{
public:
    PeriodicSignal(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period) :
            Signal(voltageOffset, timeOffset), minValue(minVoltage), maxValue(maxVoltage)
    {
       this->period = period;
    }
    virtual double getVoltageAtTime(Time t) = 0;

protected:
    double getMinVoltage() { return minValue; };
    double getMaxVoltage() { return maxValue; };
    Time getPeriod() { return period; };

private:
    double minValue;
    double maxValue;
    Time period;
};

#endif //AIRPLANEMONITOR_PERIODICSIGNAL_HPP
