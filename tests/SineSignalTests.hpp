//
// Created by duncan on 5/12/16.
//

#ifndef AIRPLANEMONITOR_SINESIGNALTESTS_HPP_HPP
#define AIRPLANEMONITOR_SINESIGNALTESTS_HPP_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "SineSignal.hpp"

using namespace Camax;

class SineTest : public ::testing::Test
{
public:
    void SetUp() {}

    void TearDown() {}

    static double sine(double voltageOffset, Time timeOffset, double minVoltage, double maxVoltage, Time period, Time t);
};


#endif //AIRPLANEMONITOR_SINESIGNALTESTS_HPP_HPP
