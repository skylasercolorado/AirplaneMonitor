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

    for(int i = 0; i <= 23; i+=10)
        for(int j = 0; j <= 59; j+=10)
            for(int k = 0; k <= 59; k+=10)
            {
                time1 = new Time(i, j, k);
                int timeInSeconds = i * 3600 + j * 60 + k;
                string verificationTime = "time in seconds: " + to_string(timeInSeconds);
                buffer.str("");
                outStream << *time1;

                delete time1;

                cout << "\n verificationTime: " << verificationTime << ". s.str(): " << buffer.str() << ".\n";
                EXPECT_EQ(verificationTime, buffer.str());
            }

    std::cout << "\n" << buffer.str() << "\n";

    std::filebuf fb;
    fb.open("test.txt", std::ios::out);

    Time time(1,0,0);
    ostream os(&fb);
    os << "Test sentence.\n";
    os << time;
    fb.close();

}

TEST_F(TimeTests, PlusAssignOperator)
{
    Time time1(0, 0, 1);
    Time time2(1, 0, 0);

    time1 += time2;

    EXPECT_EQ(1 * 3600 + 0 * 60 + 1, time1.getTotalTimeAsSeconds());
}

TEST_F(TimeTests, PlusAssignOperatorSweep)
{
    Time time1(0, 0, 0);
    Time time2(1, 1, 1);

    for(int i = 1; i < 10; i++)
    {
        time1 += time2;
        EXPECT_EQ(i*3600 + i*60 + i, time1.getTotalTimeAsSeconds());
    }
}

TEST_P(TimeParams, valueSweep)
{
    timeParams params = GetParam();

    Time time(params.hour, params.minute, params.seconds);
    std::cout <<"\n hour: " << params.hour << ". minute: " << params.minute << ". seconds: " << params.seconds << ". \n\n";
    EXPECT_EQ(params.hour * 3600 + params.minute * 60 + params.seconds, time.getTotalTimeAsSeconds());
}

std::vector<timeParams> generateParams()
{
    std::vector<timeParams> params;
    timeParams temp;

    for(int i = 0; i <= 23; i+=10)
        for(int j = 0; j <= 59; j+=10)
            for(int k = 0; k <= 59; k+=10)
                params.push_back(temp.setTimeParams(i,j,k));

    return params;
}

INSTANTIATE_TEST_CASE_P(timeParamsSweep, TimeParams, ::testing::ValuesIn(generateParams()));

