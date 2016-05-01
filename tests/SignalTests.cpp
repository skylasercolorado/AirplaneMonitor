//
// Created by duncan on 4/30/16.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Signal.hpp"

using namespace Camax;

class TestSignal : public Signal
{
public:
    TestSignal(double voltage, Time timeOffset) : Signal(voltage, timeOffset) {}

    virtual double getVoltageAtTime(Time t)
    {
        return 1.0 * t.getTotalTimeAsSeconds();
    }

    double getVoltage()
    {
        return this->getVoltageOffset();
    }

    Time getTime()
    {
        return this->getTimeOffset();
    }

};

class SignalTests : public ::testing::Test
{
public:
    void SetUp()
    {

    }

    void TearDown()
    {

    }
};

TEST_F(SignalTests, Create)
{
    int seconds = 45;
    int voltage = 23;
    double multiplier = 1.0;

    Time time1(0, 0, seconds);
    TestSignal signal1(voltage, time1);
    Signal *handle = &signal1;

    EXPECT_EQ(voltage, signal1.getVoltage());
    EXPECT_EQ(seconds, signal1.getTime().getTotalTimeAsSeconds());
    EXPECT_EQ(multiplier * seconds, handle->getVoltageAtTime(time1));
}