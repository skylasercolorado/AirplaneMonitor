//
// Created by duncan on 5/1/16.
//

#include "DataRecorderMock.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Sensor.hpp"
#include "ConstantSignal.hpp"

using namespace Camax;

class SensorTest : public Sensor
{
public:
    SensorTest(string name, Signal &source) : Sensor(name, source) {}

    virtual string getUnits()
    {
        return "test units";
    }

    string _getName()
    {
        return this->getName();
    }

    Signal& _getSource()
    {
        return this->getSource();
    }
};

class SensorTests : public ::testing::Test
{
    void SetUp() {}

    void TearDown() {}
};

TEST_F(SensorTests, ConstructAndTestAccessors)
{
    string name = "test sensor";
    int seconds = 45;
    int voltage = 23;
    ConstantSignal *signal = new ConstantSignal(voltage, Time(0, 0, seconds));

    SensorTest sensor(name, *signal);

    EXPECT_EQ(name, sensor._getName());
    EXPECT_EQ(signal->getVoltageAtTime(0), sensor._getSource().getVoltageAtTime(0));

    Signal *testSignal = &sensor._getSource();
    EXPECT_TRUE(memcmp(signal, testSignal, sizeof(ConstantSignal)) == 0);

    EXPECT_EQ("test units", sensor.getUnits());
}

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Invoke;

TEST_F(SensorTests, WithMockOfDataRecorder)
{
    string name = "test sensor";
    int seconds = 45;
    int voltage = 23;
    ConstantSignal *signal = new ConstantSignal(voltage, Time(0, 0, seconds));

    SensorTest sensor(name, *signal);

    DataRecorderMock dataRecorderMock;

    EXPECT_CALL(dataRecorderMock, log(_,_,_,_))
                .WillOnce(Invoke([&](Time timeStamp, string sensorName, double sensorVoltage, string sensorUnits)
                                 {
                                     EXPECT_EQ(name, sensorName);
                                     EXPECT_EQ(voltage, sensorVoltage);
                                     EXPECT_EQ("test units", sensorUnits);

                                 }));

    sensor.takeReading(Time(0, 0, seconds), dataRecorderMock);
}
