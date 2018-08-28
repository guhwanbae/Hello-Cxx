//  Author  :   Gu-hwan Bae
//  Date    :   28 August, 2018
//  Summary :   Make a std::thread object.
//              Section 1.4, C++ concurrency in action 1st edition

#include <iostream>
#include <thread>
// The functions and classes for managing threads are declared in <thread>.
// Whereas those for protecting shared data are declared in other heads.

void hello()
{
    std::cout<<"Hello Cocurrent World\n";
}

int main()
{
    // Every thread has to have an initial function.
    // The thread in this application has main() as initial function.
    // std::thread constructor makes initial function
    // assigned fucntor in this constructor.
    std::thread t(hello);
    t.join();

    std::cout<<"End of this program.\n";
    return 0;
}
