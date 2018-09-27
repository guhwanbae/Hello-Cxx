//  Author  :   Gu-hwan Bae
//  Date    :   27 September, 2018
//  Summary :   When delete std::future objects, there are two possible cases.
//              1) Eager taskes make the destructor, that deletes std::future object, blocked -
//                 until they finish their work.
//              2) Lazy taskes will never execute their work.
//                 (std::future objects will be deleted is the last reference to the shared state.)
//                 Therefore, the destructor is not blocked.

#ifndef FUTURE_CONTAINER_H_
#define FUTURE_CONTAINER_H_

#include <iostream>
#include <future>
#include <vector>
#include <chrono>

#include "life_timer.h"

using namespace std;

class FutureContainer {
    public :
        FutureContainer();
        ~FutureContainer();

        FutureContainer(const FutureContainer&) = delete;
        FutureContainer& operator=(const FutureContainer&) = delete;

        FutureContainer(FutureContainer&&) = default;
        FutureContainer& operator=(FutureContainer&&) = default;

        void push(future<void>&& fut);
    private :
        // LifeTimer object is declared in first order. So, This object will be destructed at the end.
        // Timer objects indicate the duration of their own life-time.
        LifeTimer timer;
        vector<future<void>> futs;
};

FutureContainer::FutureContainer() : timer {LifeTimer("FutureContainer")} {
    cout << "FutureContainer : ctor." << endl;
}

FutureContainer::~FutureContainer() {
    cout << "FutureContainer : dtor." << endl;
    // First, Container of std::future objects will be deleted.
    // Last, Timer object will be deleted.
    
    // There are two possible cases.
    // 1) Eager taskes that their launch policy is std::launch::async make this blocked until they finish their work.
    // 2) If std::future object that last reference of a shared state are deleted,
    //    lazy taskes that their launch policy is std::launch::deferred will never execute their work.
}

void FutureContainer::push(future<void>&& fut) {
    cout << "FutureContainer : push new task." << endl;
    futs.emplace_back(move(fut));
}

#endif /* FUTURE_CONTAINER_H_ */
