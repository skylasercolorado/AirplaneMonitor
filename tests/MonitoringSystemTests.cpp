//
// Created by duncan on 5/7/16.
//

#include <ConstantSignal.hpp>
#include <AngularSensor.hpp>
#include <SineSignal.hpp>
#include <PressureSensor.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MonitoringSystem.hpp"

using namespace Camax;


class MonitoringSystemTests : public ::testing::Test
{
public:
    void SetUp() {}

    void TearDown() {}

private:
};

string verificationString(Time timeStamp, string sensorName, double sensorVoltage, string sensorUnits)
{
    stringbuf buffer;
    ostream os(&buffer);

    os << timeStamp << ", sensor: " << sensorName << ", measurement: " << sensorVoltage << " (" << sensorUnits << ")\n";

    return buffer.str();
}

TEST_F(MonitoringSystemTests, ConstructAndUseOneSensor)
{
    stringbuf buffer;
    ostream os(&buffer);
    MonitoringSystem monitor(os);

    double voltage = 23.45;
    Time timeOffset(0, 0, 0);
    Signal *signal = new ConstantSignal(voltage, timeOffset);
    Sensor *sensor = new AngularSensor("Direction", *signal);

    monitor.AddSensor(sensor);
    Time samplingTime(0, 23, 45);
    monitor.TakeReading(samplingTime);

    string checkString = verificationString(samplingTime, "Direction", voltage, "radians");
    EXPECT_EQ(checkString, buffer.str());
}

TEST_F(MonitoringSystemTests, ManySensors)
{
    stringbuf buffer;
    ostream os(&buffer);
    MonitoringSystem monitor(os);

    double voltage = 23.45;
    Time timeOffset(0, 0, 0);
    Signal *signal = new ConstantSignal(voltage, timeOffset);
    Sensor *sensor = new AngularSensor("Direction", *signal);

    monitor.AddSensor(sensor);
    Time samplingTime(0, 23, 45);
    monitor.TakeReading(samplingTime);
    string checkString = verificationString(samplingTime, "Direction", voltage, "radians");
    EXPECT_EQ(checkString, buffer.str());

    buffer.str("");

    signal = new SineSignal(voltage, timeOffset, 0, 10, Time(0, 1, 0));
    sensor = new PressureSensor("Pressure", *signal);
    monitor.AddSensor(sensor);
    monitor.TakeReading(samplingTime);
    checkString += verificationString(samplingTime, "Pressure", voltage, "Pounds per square inch (PSI)");
    EXPECT_EQ(checkString, buffer.str());
}
