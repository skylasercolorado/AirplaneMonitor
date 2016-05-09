//
// Created by duncan on 5/9/16.
//

#ifndef AIRPLANEMONITOR_SAWTOOTHSIGNALTESTS_HPP
#define AIRPLANEMONITOR_SAWTOOTHSIGNALTESTS_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace Camax;

class SawTests : public ::testing::Test
{
public:
    void SetUp() {}

    void TearDown() {}

    double saw(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period, Time t);
};

#endif //AIRPLANEMONITOR_SAWTOOTHSIGNALTESTS_HPP
