//
// Created by duncan on 4/30/16.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "SawtoothSignal.hpp"

using namespace Camax;

class SawTests : public ::testing::Test
{
    void SetUp() {}

    void TearDown() {}

    void saw(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period, Time t);
};

TEST_F(SawTests, CreateAndSweepValues)
{

}

