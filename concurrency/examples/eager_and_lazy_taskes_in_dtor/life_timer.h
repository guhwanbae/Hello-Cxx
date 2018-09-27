//  Author  :   Gu-hwan Bae
//  Date    :   27 September, 2018
//  Summary :   LifeTimer object indicates the duration of their own life-time.

#ifndef LIFE_TIMER_H_
#define LIFE_TIMER_H_

#include <iostream>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

class LifeTimer {
    public :
        explicit LifeTimer(const string& logging_tag);
        ~LifeTimer();

        LifeTimer(const LifeTimer&) = delete;
        LifeTimer& operator=(const LifeTimer&) = delete;

        LifeTimer(LifeTimer&&) = default;
        LifeTimer& operator=(LifeTimer&&) = default;
    private :
        time_point<high_resolution_clock> start_point;
        string tag;
};

LifeTimer::LifeTimer(const string& logging_tag)
    : start_point { high_resolution_clock::now() }, tag { logging_tag }
{
}

LifeTimer::~LifeTimer()
{
    auto end_point = high_resolution_clock::now();
    auto life_time_mills = (duration_cast<milliseconds>(end_point - start_point)).count();
    std::cout << tag << "::Life Time : " << life_time_mills << " ms." << std::endl;
}

#endif  /* LIFE_TIMER_H_ */
