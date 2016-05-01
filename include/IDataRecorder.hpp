//
// Created by duncan on 5/1/16.
//

#ifndef AIRPLANEMONITOR_IDATARECORDER_HPP
#define AIRPLANEMONITOR_IDATARECORDER_HPP

#include <ostream>
#include "Time.hpp"

namespace Camax
{
    class IDataRecorder
    {
    public:
        virtual ~IDataRecorder() {}
        virtual void log(Time timeStamp, string sensorName, double sensorVoltage, string sensorUnits) = 0;
    };
}

#endif //AIRPLANEMONITOR_IDATARECORDER_HPP
