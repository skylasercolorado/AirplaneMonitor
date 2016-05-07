//
// Created by duncan on 4/29/16.
//

#include "Time.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <ostream>
#include <fstream>

using namespace Camax;
using namespace std;

static const int maxHours = 23;
static const int maxMinutes = 59;
static const int maxSeconds = 59;
static const int timeIncrement = 20;

class TimeTests : public ::testing::Test
{
public:
    void SetUp()
    {
    }

    void TearDown()
    {
    }
};

struct timeParams
{
    int hour;
    int minute;
    int seconds;

    timeParams(int hour = 0, int minute = 0, int seconds = 0)
    {
        this->hour = hour;
        this->minute = minute;
        this->seconds = seconds;
    }

    timeParams setTimeParams(int hour, int minute, int seconds)
    {
        this->hour = hour;
        this->minute = minute;
        this->seconds = seconds;

        return *this;
    }
};

class TimeParams : public TimeTests, public ::testing::WithParamInterface<timeParams>
{
public:
    void SetUp()
    {
    }

    void TearDown()
    {
    }

private:

};

TEST_F(TimeTests, Create)
{
    Time time(0, 0, 1);

    EXPECT_EQ(1, time.getTotalTimeAsSeconds());
}

TEST_F(TimeTests, TestOperatorOstream)
{
    Time *time1;
    stringbuf buffer;
    ostream outStream(&buffer);

    for(int i = 0; i <= maxHours; i+= timeIncrement)
        for(int j = 0; j <= maxMinutes; j+=timeIncrement)
            for(int k = 0; k <= maxSeconds; k+=timeIncrement)
            {
                time1 = new Time(i, j, k);
                int timeInSeconds = i * secondsInAnHour + j * secondsInAMinute + k;
                string verificationTime = "Time: " + to_string(timeInSeconds) + " (seconds)";
                buffer.str("");
                outStream << *time1;

                delete time1;

                EXPECT_EQ(verificationTime, buffer.str());
            }
}

TEST_F(TimeTests, TestOperatorOstreamWithFile)
{
    Time *time1;
    std::filebuf writeHandle;
    ostream outputStream(&writeHandle);

    std::filebuf readHandle;
    istream inputStream(&readHandle);
    string buffer;
    string testFileName = "test.txt";

    for(int i = 0; i <= maxHours; i+=timeIncrement)
        for(int j = 0; j <= maxMinutes; j+=timeIncrement)
            for(int k = 0; k <= maxSeconds; k+=timeIncrement)
            {
                time1 = new Time(i, j, k);
                int timeInSeconds = i * secondsInAnHour + j * secondsInAMinute + k;
                string verificationTime = "Time: " + to_string(timeInSeconds) + " (seconds)";

                writeHandle.open(testFileName, std::ios::out);
                outputStream << *time1;
                writeHandle.close();

                delete time1;

                inputStream.clear();
                buffer.clear();
                readHandle.open(testFileName, std::ios::in);

                char c;
                while(inputStream.get(c))
                    buffer += c;
                readHandle.close();

                EXPECT_EQ(verificationTime, buffer);
            }
}

TEST_F(TimeTests, PlusAssignOperator)
{
    Time time1(0, 0, 1);
    Time time2(1, 0, 0);

    time1 += time2;

    EXPECT_EQ(1 * secondsInAnHour + 0 * secondsInAMinute + 1, time1.getTotalTimeAsSeconds());
}

TEST_F(TimeTests, PlusAssignOperatorSweep)
{
    Time time1(0, 0, 0);
    Time time2(1, 1, 1);

    for(int i = 1; i < 10; i++)
    {
        time1 += time2;
        EXPECT_EQ(i*secondsInAnHour + i*secondsInAMinute + i, time1.getTotalTimeAsSeconds());
    }
}

TEST_P(TimeParams, valueSweep)
{
    timeParams params = GetParam();

    Time time(params.hour, params.minute, params.seconds);
    EXPECT_EQ(params.hour * secondsInAnHour + params.minute * secondsInAMinute + params.seconds, time.getTotalTimeAsSeconds());
}

std::vector<timeParams> generateParams()
{
    std::vector<timeParams> params;
    timeParams temp;

    for(int i = 0; i <= maxHours; i+=timeIncrement)
        for(int j = 0; j <= maxMinutes; j+=timeIncrement)
            for(int k = 0; k <= maxSeconds; k+=timeIncrement)
                params.push_back(temp.setTimeParams(i,j,k));

    return params;
}

INSTANTIATE_TEST_CASE_P(timeParamsSweep, TimeParams, ::testing::ValuesIn(generateParams()));

