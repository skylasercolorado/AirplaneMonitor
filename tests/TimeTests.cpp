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
static const int timeIncrement = 10;

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
                int timeInSeconds = i * Time::secondsInAnHour + j * Time::secondsInAMinute + k;
                string verificationTime = "time in seconds: " + to_string(timeInSeconds);
                buffer.str("");
                outStream << *time1;

                delete time1;

//                cout << "\n verificationTime: " << verificationTime << ". s.str(): " << buffer.str() << ".\n";
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

    for(int i = 0; i <= maxHours; i+=timeIncrement)
        for(int j = 0; j <= maxMinutes; j+=timeIncrement)
            for(int k = 0; k <= maxSeconds; k+=timeIncrement)
            {
                time1 = new Time(i, j, k);
                int timeInSeconds = i * Time::secondsInAnHour + j * Time::secondsInAMinute + k;
                string verificationTime = "time in seconds: " + to_string(timeInSeconds);

                writeHandle.open("test.txt", std::ios::out);
                outputStream << *time1;
                writeHandle.close();

                delete time1;

                inputStream.clear();
                buffer.clear();
                readHandle.open("test.txt", std::ios::in);

                char c;
                while(inputStream.get(c))
                    buffer += c;
                readHandle.close();

//                cout << "\n verificationTime: " << verificationTime << ". buffer: " << buffer << ".\n";
                EXPECT_EQ(verificationTime, buffer);
            }
}

TEST_F(TimeTests, PlusAssignOperator)
{
    Time time1(0, 0, 1);
    Time time2(1, 0, 0);

    time1 += time2;

    EXPECT_EQ(1 * Time::secondsInAnHour + 0 * Time::secondsInAMinute + 1, time1.getTotalTimeAsSeconds());
}

TEST_F(TimeTests, PlusAssignOperatorSweep)
{
    Time time1(0, 0, 0);
    Time time2(1, 1, 1);

    for(int i = 1; i < 10; i++)
    {
        time1 += time2;
        EXPECT_EQ(i*Time::secondsInAnHour + i*Time::secondsInAMinute + i, time1.getTotalTimeAsSeconds());
    }
}

TEST_P(TimeParams, valueSweep)
{
    timeParams params = GetParam();

    Time time(params.hour, params.minute, params.seconds);
//    std::cout <<"\n hour: " << params.hour << ". minute: " << params.minute << ". seconds: " << params.seconds << ". \n\n";
    EXPECT_EQ(params.hour * Time::secondsInAnHour + params.minute * Time::secondsInAMinute + params.seconds, time.getTotalTimeAsSeconds());
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

