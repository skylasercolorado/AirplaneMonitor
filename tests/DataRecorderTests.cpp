//
// Created by duncan on 5/5/16.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "DataRecorder.hpp"

using namespace Camax;

class DataRecorderTests : public ::testing::Test
{
public:
    DataRecorderTests() : timeStamp(0, 0, seconds) {}
    virtual void SetUp() {}

    virtual void TearDown() {}

    int seconds = 45;
    Time timeStamp;
    string sensorName = "test sensor";
    double sensorVoltage = 23;
    string sensorUnits = "test units";
};

TEST_F(DataRecorderTests, Construct)
{
    stringbuf s;
    ostream os(&s);

    DataRecorder testRecorder (os);

    testRecorder.log(timeStamp, sensorName, sensorVoltage, sensorUnits);

    stringbuf spec;
    ostream testos(&spec);

    testos << timeStamp << ", " << sensorName << ", " << sensorVoltage << ", " << sensorUnits;

    EXPECT_EQ(spec.str(), s.str());
}
