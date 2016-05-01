//
// Created by duncan on 4/30/16.
//

#include <ConstantSignal.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace Camax;

class ConstantSignalTest : public ::testing::Test
{
    void SetUp() {}

    void TearDown() {}
};

TEST_F(ConstantSignalTest, ConstructAndGetVoltage)
{
    Time time1(0, 0, 23);
    double voltage = 45;

    ConstantSignal constSignal (voltage, time1);

    EXPECT_EQ(voltage, constSignal.getVoltageAtTime(time1));
}
