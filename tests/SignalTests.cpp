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
    Time b(0,0,45);
    TestSignal a(23, b);
    Signal *handle = &a;

    EXPECT_EQ(23, a.getVoltage());
    EXPECT_EQ(45, a.getTime().getTotalTimeAsSeconds());
    EXPECT_EQ(1.0 * 45, handle->getVoltageAtTime(b));
}