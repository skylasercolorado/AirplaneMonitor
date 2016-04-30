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
        Time(int hours = 0, int minutes = 0, int seconds = 0);
        int getTotalTimeAsSeconds() const;
        const Time& operator+=(const Time& rhs);
        friend ostream& operator<<(ostream& os, const Time& time);

        const int secondsInAnHour = 3600;
        const int secondsInAMinute = 60;

    private:
        int seconds;
    };
}

#endif //AIRPLANEMONITOR_TIME_HPP
