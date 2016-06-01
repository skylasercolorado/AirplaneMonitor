//
// Created by duncan on 6/1/16.
//

#include <ConstantSignal.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AngularSensor.hpp"

using namespace Camax;

class AngularSensorTest : public AngularSensor
{
public:
    AngularSensorTest(string name, Signal& source) : AngularSensor(name, source) {}

    string GetUnits()
    {
        return this->getUnits();
    }
};

class AngularSensorTests : public ::testing::Test
{
    void SetUp() {}

    void TearDown() {}


};

TEST_F(AngularSensorTests, getUnits)
{
    string name = "angular sensor";
    double voltageOffset = 10.0;
    Time timeOffset(0, 0, 10);
    ConstantSignal signal(voltageOffset, timeOffset);
    AngularSensorTest angularSensor(name, signal);

    const string angularUnits = "radians";
    EXPECT_EQ(angularUnits, angularSensor.GetUnits());
}
