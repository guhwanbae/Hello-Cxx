#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

struct critical_data {
    std::mutex mtx;
};

void dead_lock(critical_data& a, critical_data& b) {
    // atomically lock mutexes as single operation.
    std::lock(a.mtx, b.mtx);
    
    // adopt lock strategy assumes that mutexes are already acqured.
    std::unique_lock<std::mutex> guard_1(a.mtx, std::adopt_lock);
    std::cout << "thread id : " << std::this_thread::get_id() << " first mutex." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::unique_lock<std::mutex> guard_2(b.mtx, std::adopt_lock);
    std::cout << "thread id : " << std::this_thread::get_id() << " second mutex." << std::endl;

    std::cout << "thread id : " << std::this_thread::get_id() << " do something." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

int main() {
    critical_data c1;
    critical_data c2;

    std::thread t1([&c1, &c2]() {   
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            dead_lock(c1, c2);
    });
    std::thread t2([&c1, &c2]() {   dead_lock(c2, c1);  });

    t1.join();
    t2.join();

    std::cout << "End of this program." << std::endl;
    return 0;
}
