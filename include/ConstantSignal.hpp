//
// Created by duncan on 4/30/16.
//

#ifndef AIRPLANEMONITOR_CONSTANTSIGNAL_HPP
#define AIRPLANEMONITOR_CONSTANTSIGNAL_HPP

#include "Signal.hpp"

using namespace Camax;

class ConstantSignal : public Signal
{
public:
    ConstantSignal(double voltageOffset, Time timeOffset) : Signal(voltageOffset, timeOffset) {}
    double getVoltageAtTime(Time t)
    {
        return this->getVoltageOffset();
    }
};

#endif //AIRPLANEMONITOR_CONSTANTSIGNAL_HPP
