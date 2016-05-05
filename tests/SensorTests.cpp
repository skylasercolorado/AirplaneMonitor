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
public:

    SensorTests() : time1(0, 0, seconds)
    {
        signal = new ConstantSignal(voltage, time1);
        sensor = new SensorTest(name, *signal);
    }

    void SetUp() {}

    void TearDown() {}

    string name = "test sensor";
    int seconds = 45;
    int voltage = 23;
//    Time time1(0, 0, seconds);
//    ConstantSignal *signal = new ConstantSignal(voltage, time1);
//    SensorTest sensor(name, *signal);
    Time time1;
    ConstantSignal *signal;
    SensorTest *sensor;
};

TEST_F(SensorTests, ConstructAndTestAccessors)
{
//    string name = "test sensor";
//    int seconds = 45;
//    int voltage = 23;
//    Time time1(0, 0, seconds);
//    ConstantSignal *signal = new ConstantSignal(voltage, time1);
//    SensorTest sensor(name, *signal);

    EXPECT_EQ(name, sensor->_getName());
    EXPECT_EQ(signal->getVoltageAtTime(0), sensor->_getSource().getVoltageAtTime(0));

    Signal *testSignal = &sensor->_getSource();
    EXPECT_TRUE(memcmp(signal, testSignal, sizeof(ConstantSignal)) == 0);

    EXPECT_EQ("test units", sensor->getUnits());

    delete signal;
}

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Invoke;

TEST_F(SensorTests, WithMockOfDataRecorder)
{
//    string name = "test sensor";
//    int seconds = 45;
//    int voltage = 23;
//    Time time1(0, 0, seconds);
//    ConstantSignal *signal = new ConstantSignal(voltage, time1);
//    SensorTest sensor(name, *signal);

    DataRecorderMock dataRecorderMock;

    EXPECT_CALL(dataRecorderMock, log(_,_,_,_))
                .WillOnce(Invoke([&](Time timeStamp, string sensorName, double sensorVoltage, string sensorUnits)
                                 {
                                     EXPECT_EQ(name, sensorName);
                                     EXPECT_EQ(voltage, sensorVoltage);
                                     EXPECT_EQ("test units", sensorUnits);
                                     EXPECT_EQ(time1.getTotalTimeAsSeconds(), timeStamp.getTotalTimeAsSeconds());

                                 }));

    sensor->takeReading(time1, dataRecorderMock);

    delete signal;
}
