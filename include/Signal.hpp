//
// Created by duncan on 4/30/16.
//

#ifndef AIRPLANEMONITOR_SIGNAL_HPP
#define AIRPLANEMONITOR_SIGNAL_HPP

#include "Time.hpp"

namespace Camax
{
    class Signal
    {
    public:
        Signal(double valueOffset, Time timeOffset)
        {
            this->voltageOffset = valueOffset;
            this->timeOffset = timeOffset;
        }
        virtual ~Signal() {}
        virtual double getVoltageAtTime(Time t) = 0;

    protected:
        double getVoltageOffset() { return voltageOffset; }
        Time getTimeOffset() { return timeOffset; }

    private:
        double voltageOffset;
        Time timeOffset;
    };
}
#endif //AIRPLANEMONITOR_SIGNAL_HPP
