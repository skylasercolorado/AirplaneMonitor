//
// Created by duncan on 4/30/16.
//

#include <fstream>
#include "SineSignalTests.hpp"
//#include "gtest/gtest.h"
//#include "gmock/gmock.h"
//#include "SineSignal.hpp"
//
//using namespace Camax;
//
//class SineTest : public ::testing::Test
//{
//public:
//    void SetUp() {}
//
//    void TearDown() {}
//
//    double sine(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period, Time t);
//};

double SineTest::sine(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period, Time t)
{
    double first = voltageOffset + minVoltage + (maxVoltage - minVoltage) / 2;
    double second = sin((t.getTotalTimeAsSeconds() + timeOffset.getTotalTimeAsSeconds()) * 2 * Pi / period.getTotalTimeAsSeconds())
                    * (maxVoltage - minVoltage) / 2;

    return (first + second);
}

TEST_F(SineTest, TestSineValue)
{
    double voltageOffset = 23;
    Time timeOffset(0, 0, 45);
    double minVoltage = 1;
    double maxVoltage = 10;
    Time period(0, 0, 60);

    std::filebuf fb;
    fb.open("sine.csv", std::ios::out);
    ostream os(&fb);
    os << "t (seconds), sin(t)\n";

    SineSignal sineSignal(voltageOffset, timeOffset, minVoltage, maxVoltage, period);

    for(int i = 0; i < 1000; i += 1)
    {
        Time t(0, 0, i);

        double refValue = sine(voltageOffset, timeOffset, minVoltage, maxVoltage, period, t);
        os << t.getTotalTimeAsSeconds() << ", " << refValue << "\n";

        EXPECT_EQ(refValue, sineSignal.getVoltageAtTime(t));
    }
}
