//
// Created by duncan on 5/5/16.
//

#include <fstream>
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

TEST_F(DataRecorderTests, ConstructAndUseStringbuf)
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

TEST_F(DataRecorderTests, ConstructAndUseFile)
{
    string testFileName = "datarecorder.txt";
    filebuf s;
    s.open(testFileName, std::ios::out);
    ostream os(&s);

    DataRecorder testRecorder (os);

    testRecorder.log(timeStamp, sensorName, sensorVoltage, sensorUnits);

    s.close();

    filebuf spec;
    spec.open(testFileName, std::ios::in);
    istream testos(&spec);

    string readStringFromFile;

    std::getline(testos, readStringFromFile);

    stringbuf verificationString;
    ostream fixtureOs(&verificationString);

    fixtureOs << timeStamp << ", " << sensorName << ", " << sensorVoltage << ", " << sensorUnits;

    EXPECT_EQ(verificationString.str(), readStringFromFile);
}
