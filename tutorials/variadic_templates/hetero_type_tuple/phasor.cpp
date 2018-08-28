//  Author  :   Gu-hwan Bae
//  Date    :   28 August, 2018
//  Summary :   Phasor struct as polar form expr.

#include <iostream>

#include "phasor.h"

std::ostream& operator<<(std::ostream& os, const Phasor& phs)
{
    os << "[amp:" << phs.a << ",dir:" << phs.d << ']';
    return os;
}
