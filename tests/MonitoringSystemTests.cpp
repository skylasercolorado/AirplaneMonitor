//
// Created by duncan on 5/7/16.
//

#include <ConstantSignal.hpp>
#include <AngularSensor.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MonitoringSystem.hpp"

using namespace Camax;

class MonitoringSystemTests : public ::testing::Test
{
    void SetUp() {}

    void TearDown() {}
};

TEST_F(MonitoringSystemTests, ConstructAndUseOneSensor)
{
    stringbuf buffer;
    ostream os(&buffer);

    MonitoringSystem monitor(os);

    double voltage = 23.45;
    Time time1(0, 10, 10);
    Signal *signal = new ConstantSignal(voltage, time1);

    Sensor *sensor = new AngularSensor("Direction", *signal);

    monitor.AddSensor(sensor);
    monitor.TakeReading(time1);

}
