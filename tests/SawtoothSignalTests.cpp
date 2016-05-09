//
// Created by duncan on 4/30/16.
//

#include <fstream>
#include "SawtoothSignal.hpp"
#include "SawtoothSignalTests.hpp"

double SawTests::saw(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period, Time t)
{
    double first = voltageOffset + minVoltage;
    double second = fmod(((t.getTotalTimeAsSeconds() + timeOffset.getTotalTimeAsSeconds()) *
                          (maxVoltage - minVoltage) / period.getTotalTimeAsSeconds()),
                         (maxVoltage - minVoltage));

    return (first + second);
}

TEST_F(SawTests, CreateAndSweepValues)
{
    double voltageOffset = 23;
    Time timeOffset(0, 0, 45);
    double minVoltage = 1;
    double maxVoltage = 10;
    Time period(0, 0, 60);

    SawtoothSignal signal1(voltageOffset, timeOffset, minVoltage, maxVoltage, period);

    std::filebuf fb;
    fb.open("saw.csv", std::ios::out);
    ostream os(&fb);

    os << "t (seconds), saw(t)\n";

    for(int i = 0; i < 1000; i += 1)
    {
        Time time1(0, 0, i);

        double refValue = saw(voltageOffset, timeOffset, minVoltage, maxVoltage, period, time1);

        EXPECT_EQ(refValue, signal1.getVoltageAtTime(time1));

        os << time1.getTotalTimeAsSeconds() << ", " << refValue << "\n";
    }

}

