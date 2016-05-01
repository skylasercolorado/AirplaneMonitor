//
// Created by duncan on 4/30/16.
//

#ifndef AIRPLANEMONITOR_SINESIGNAL_HPP
#define AIRPLANEMONITOR_SINESIGNAL_HPP

#include "PeriodicSignal.hpp"
#include <cmath>

namespace Camax
{
    const double Pi = 3.14159265358979323846;

    class SineSignal : public PeriodicSignal
    {
    public:
        SineSignal(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period)
                : PeriodicSignal(voltageOffset, timeOffset, minVoltage, maxVoltage, period) {}

        double getVoltageAtTime(Time t)
        {
            double firstPart = this->getVoltageOffset() + this->getMinVoltage() + (this->getMaxVoltage() - this->getMinVoltage()) / 2;
            double secondsPart = sin((t.getTotalTimeAsSeconds() + this->getTimeOffset().getTotalTimeAsSeconds()) * 2
                                     * Pi / this->getPeriod().getTotalTimeAsSeconds()) / 2;

            return (firstPart + secondsPart);
        }
    };
}

#endif //AIRPLANEMONITOR_SINESIGNAL_HPP
