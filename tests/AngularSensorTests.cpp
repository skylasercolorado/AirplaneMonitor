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
public:
    const string angularUnits = "radians";

    AngularSensorTests() : timeOffset(0, 0, 10), signal(voltageOffset, timeOffset), angularSensor(name, signal)
    {}

    void SetUp() {}

    void TearDown() {}

    string name = "angular sensor";
    double voltageOffset = 10.0;
    Time timeOffset;
    ConstantSignal signal;
    AngularSensorTest angularSensor;
};

TEST_F(AngularSensorTests, getUnits)
{
    EXPECT_EQ(angularUnits, angularSensor.GetUnits());
}
