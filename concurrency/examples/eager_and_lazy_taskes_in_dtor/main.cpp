//  Author  :   Gu-hwan Bae
//  Date    :   27 September, 2018
//  Summary :   When delete std::future objects, there are two possible cases.
//              1) Eager taskes make the destructor, that deletes std::future object, blocked -
//                 until they finish their work.
//              2) Lazy taskes will never execute their work.
//                 (std::future objects will be deleted is the last reference to the shared state.)
//                 Therefore, the destructor is not blocked.

#include <iostream>
#include <future>
#include <vector>
#include <string>
#include <chrono>

#include "future_container.h"
#include "life_timer.h"

using namespace std;

void launch_eager_taskes() {
    cout << "\n----------------------------------------------------------------" << endl;
    cout << "launc_eager_taskes() : begin." << endl;

    auto wait_and_log = [](const string& tag, int mills) {
        LifeTimer timer {tag};
        this_thread::sleep_for(chrono::milliseconds(mills));
    };

    FutureContainer fcon;
    
    // Eager taskes.
    fcon.push(async(launch::async, wait_and_log, "task1", 1000));
    fcon.push(async(launch::async, wait_and_log, "task2", 2000));
    fcon.push(async(launch::async, wait_and_log, "task3", 3000));
    fcon.push(async(launch::async, wait_and_log, "task4", 4000));
    fcon.push(async(launch::async, wait_and_log, "task5", 5000));

    cout << "launch_eager_taskes() : End of launch_lazy_taskes()." << endl;
    // FutureContainer object is deleted here.
    // And deleting std::future objects that refer to eager taskes is deferred until eager taskes finish their work.
    // The main thread is blocked until above job is completed.
}

void launch_lazy_taskes() {
    cout << "\n----------------------------------------------------------------" << endl;
    cout << "launc_lazy_taskes() : begin." << endl;

    auto wait_and_log = [](const string& tag, int mills) {
        LifeTimer timer {tag};
        this_thread::sleep_for(chrono::milliseconds(mills));
    };

    FutureContainer fcon;
    
    // Lazy taskes.
    fcon.push(async(launch::deferred, wait_and_log, "task1", 1000));
    fcon.push(async(launch::deferred, wait_and_log, "task2", 2000));
    fcon.push(async(launch::deferred, wait_and_log, "task3", 3000));
    fcon.push(async(launch::deferred, wait_and_log, "task4", 4000));
    fcon.push(async(launch::deferred, wait_and_log, "task5", 5000));

    cout << "launch_lazy_taskes() : End of launch_lazy_taskes()." << endl;
    // FutureContainer object is deleted here. And lazy taskes never execute their work.
    // The main thread is not blocked.
}

int main() {
    launch_eager_taskes();
    launch_lazy_taskes();
    cout << "main() : End of this program." << endl;
    return 0;
}
