//
// Created by duncan on 4/30/16.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "PeriodicSignal.hpp"

using namespace Camax;

class PeriodicTestSignal : public PeriodicSignal
{
public:
    PeriodicTestSignal(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period)
            : PeriodicSignal(voltageOffset, timeOffset, minVoltage, maxVoltage, period) {}

    double getVoltageAtTime(Time t)
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

    double getMin()
    {
        return this->getMinVoltage();
    }

    double getMax()
    {
        return this->getMaxVoltage();
    }

    Time getThisPeriod()
    {
        return this->getPeriod();
    }
};

class PeriodicSignalTest : public ::testing::Test
{
    void SetUp() {}

    void TearDown() {}
};

TEST_F(PeriodicSignalTest, ConstructAndTestAccessorsAndPureVirtualImplementation)
{
    double voltage = 45;
    double seconds = 23;
    Time time(0, 0, seconds);
    double minVal = 1;
    double maxVal = 10;
    double period = 60;

    PeriodicTestSignal signal1(voltage, time, minVal, maxVal, period);

    EXPECT_EQ(voltage, signal1.getVoltage());
}
