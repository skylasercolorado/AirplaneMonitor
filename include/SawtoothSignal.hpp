//
// Created by duncan on 4/30/16.
//

#ifndef AIRPLANEMONITOR_SAWTOOTHSIGNAL_HPP
#define AIRPLANEMONITOR_SAWTOOTHSIGNAL_HPP

#include "PeriodicSignal.hpp"

namespace Camax
{
    class SawtoothSignal : public PeriodicSignal
    {
        SawtoothSignal(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period)
                : PeriodicSignal(voltageOffset, timeOffset, minVoltage, maxVoltage, period) {}

        double getVoltageAtTime(Time t)
        {
            double firstPart = this->getVoltageOffset() + this->getMinVoltage();
            double secondPart = ((t.getTotalTimeAsSeconds() + this->getTimeOffset().getTotalTimeAsSeconds()) *
                    (this->getMaxVoltage() - this->getMinVoltage()) / this->getPeriod()) % (this->getMaxVoltage() - this->getMinVoltage());

            return (firstPart + secondPart);
        }
    };
}

#endif //AIRPLANEMONITOR_SAWTOOTHSIGNAL_HPP
