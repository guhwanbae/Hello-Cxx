/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   30 August, 2018
 *  Summary :   testing a thread-safe stack.
 */

#include <iostream>
#include <thread>
#include <mutex>

#include "threadsafe_stack.h"

void foo()
{
    threadsafe_stack<int> ts;

    auto producer = [&ts](const int n) {
        for(int i=0;i<n;++i)
        {
            ts.push(static_cast<int>(n));
        }
    };

    auto consumer = [&ts](int cnt) {
        int elem {0};
        while(cnt > 0)
        {
            try {
                ts.pop(elem);
                std::cout<<"stack["<<cnt--<<"] : "<<elem<<'\n';
            }
            catch(const empty_stack& msg) {
                std::cout<<msg.what()<<'\n';
            }
        }
    };

    std::thread t1(producer, 111111);
    std::thread t2(producer, 222222);
    std::thread t3(consumer, 333333);

    t1.join();
    t2.join();
    t3.join();
}

int main()
{
    foo();
    return 0;
}
