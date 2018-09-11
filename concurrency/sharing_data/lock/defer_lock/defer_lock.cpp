#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

struct critical_data {
    std::mutex mtx;
};

void dead_lock(critical_data& a, critical_data& b) {
    // defer_lock strategy assumes that mutexes are not acquired on construction.
    // do not acquire ownership of the mutex in here!
    std::unique_lock<std::mutex> guard_1(a.mtx, std::defer_lock);
    std::cout << "thread id : " << std::this_thread::get_id() << " first mutex." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::unique_lock<std::mutex> guard_2(b.mtx, std::defer_lock);
    std::cout << "thread id : " << std::this_thread::get_id() << " second mutex." << std::endl;
    
    // atomically lock mutexes as single operation.
    std::lock(guard_1, guard_2);
    std::cout << "thread id : " << std::this_thread::get_id() << " do something." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

int main() {
    critical_data c1;
    critical_data c2;

    std::thread t1([&c1, &c2]() {   dead_lock(c1, c2);  });
    std::thread t2([&c1, &c2]() {   dead_lock(c2, c1);  });

    t1.join();
    t2.join();

    std::cout << "End of this program." << std::endl;
    return 0;
}
