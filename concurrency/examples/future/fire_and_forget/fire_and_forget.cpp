//  Author  :   Gu-hwan Bae
//  Date    :   13 September, 2018
//  Summary :   Fire and forget std::async task. Main thread will be blocked -
//              as soon as this std::async object is created. Because it is anonymous -
//              object, It will be destructed immediately. And wait for task to finish -
//              at its destructor.

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int main() {
    std::thread counter([](int sleep_for) {
        while(sleep_for > 0) {
            std::cout << sleep_for-- << " seconds left..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        }, 10);

    std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "End of first task." << std::endl;
    });

    std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "End of second task." << std::endl;
    });

    counter.join();
    std::cout << "End of this program." << std::endl;
    return 0;
}
