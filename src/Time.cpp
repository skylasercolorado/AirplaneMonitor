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

int Time::getTotalTimeAsSeconds() const
{
    return seconds;
}

const Time& Time::operator+=(const Time& rhs)
{
    this->seconds += rhs.seconds;

    return *this;
}

namespace Camax
{
    ostream& operator<<(ostream& os, const Time& time)
    {
        os << "time in seconds: " << time.getTotalTimeAsSeconds();

        return os;
    }
}
