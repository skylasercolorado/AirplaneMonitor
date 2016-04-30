//
// Created by duncan on 4/29/16.
//

#ifndef AIRPLANEMONITOR_TIME_HPP
#define AIRPLANEMONITOR_TIME_HPP

#include <ostream>

using namespace std;

namespace Camax
{
    class Time
    {
    public:
        Time(int hours, int minutes, int seconds);
        int getTotalTimeAsSeconds() const;
        const int secondsInAnHour = 3600;
        const int secondsInAMinute = 60;
        const Time& operator+=(const Time& rhs);
        friend ostream& operator<<(ostream& os, const Time& time);

    private:
        int seconds;
    };
}

#endif //AIRPLANEMONITOR_TIME_HPP
