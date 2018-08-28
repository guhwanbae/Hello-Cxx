//  Author  :   Gu-hwan Bae
//  Date    :   28 August, 2018
//  Summary :   Phasor struct as polar form expr.

#include <iostream>

struct Phasor
{
    Phasor(double amplitude, double direction) : \
        a{amplitude}, d{direction} {}
    double a;
    double d;
};

std::ostream& operator<<(std::ostream& os, const Phasor& phs);
