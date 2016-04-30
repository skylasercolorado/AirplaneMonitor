//
// Created by duncan on 4/29/16.
//

#include "Time.hpp"

using namespace Camax;

Time::Time(int hours, int minute, int seconds)
{
    this->seconds = hours * secondsInAnHour +
                    minute * secondsInAMinute +
                    seconds;
}

int Time::getTotalTimeAsSeconds()
{
    return seconds;
}