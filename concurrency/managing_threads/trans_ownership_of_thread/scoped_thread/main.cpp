/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   29 August, 2018
 *  Summary :   Transferring ownership of a thread to 'scoped_thread' class.
 *              It's ensuring thread are completed before a scope is exited.
 */

#include <iostream>
#include <thread>

#include "scoped_thread.h"

void do_something_in_current_thread()
{
    std::cout << "Something Task..." << std::endl;
}

void foo()
{
    auto job = []() { std::cout << "hello" << std::endl; };
    // temporary(rvalue) objects are moving automatically and implicitly.
    scoped_thread st{ std::thread(job) };

    do_something_in_current_thread();
    std::cout << "End of foo()." << std::endl;
}

int main()
{
    foo();
    std::cout << "End of this program." << std::endl;
    return 0;
}
