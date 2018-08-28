//  Author  :   Gu-hwan Bae
//  Date    :   28 August, 2018
//  Summary :   Test a 'package' class.

#include <iostream>
#include <string>

#include "package.h"
#include "for_each_tuple.h"
#include "phasor.h"

void foo()
{
    Package<int, double, std::string> p1 {123, 0.123, "one two three"};
    p1.print_elements();

    using circuit_analysis = Package<std::string, Phasor, std::string, Phasor>;
    circuit_analysis p2 {"Voltage(V)", Phasor{220, 0}, \
                        "Current(mA)", Phasor{600, 5.6}};
    p2.print_elements();
}

int main()
{
    foo();
    return 0;
}
