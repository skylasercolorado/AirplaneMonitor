//
// Created by duncan on 5/1/16.
//

#ifndef AIRPLANEMONITOR_DATARECORDERMOCK_HPP
#define AIRPLANEMONITOR_DATARECORDERMOCK_HPP

#include "IDataRecorder.hpp"
#include "gmock/gmock.h"
#include "Time.hpp"

namespace Camax
{
    class DataRecorderMock : public IDataRecorder
    {
    public:
        MOCK_METHOD4(log, void (Time timeStamp, string sensorName, double sensorVoltage, string sensorUnits));
    };
}
#endif //AIRPLANEMONITOR_DATARECORDERMOCK_HPP
