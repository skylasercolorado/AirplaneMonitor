//
// Created by duncan on 5/1/16.
//

#ifndef AIRPLANEMONITOR_DATARECORDER_HPP
#define AIRPLANEMONITOR_DATARECORDER_HPP

#include "IDataRecorder.hpp"

namespace Camax
{
    class DataRecorder : IDataRecorder
    {
    public:
        DataRecorder(ostream &out) : out(out) {}
        virtual void log(Time timeStamp, string sensorName, double sensorVoltage, string sensorUnits);

    private:
        ostream &out;
    };
}
#endif //AIRPLANEMONITOR_DATARECORDER_HPP
