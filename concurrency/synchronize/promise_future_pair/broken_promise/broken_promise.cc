// Author   :   Gu-hwan Bae
// Date     :   11 December, 2018
// Summary  :   Broken promise example, the std::future_error exception could be invoked
//              when destroying the promise object without value or exception providing one.

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <utility>

namespace {

void counter_job(const int time_out) {
    std::cout << "Wait for " << time_out << " ms..." << std::endl;
    constexpr int time_step {1000};
    for(int cnt=time_step; cnt<=time_out; cnt+=time_step) {
        std::cout << "Timeout : " << time_out-cnt << " ms left..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_step));
    }
}

}  // namespace anonymouse

int main() {
    auto prepare_job = [](std::promise<void> prom) {
        constexpr int delay_milli {5000};
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_milli));
        std::cout << "End of the prepare job..." << std::endl;
        // Destroying std::promise object without value or exception providing one.
        // std::future_error exception will be invoked here.
    };

    auto post_job = [](std::future<void> fut) {
        std::cout << "Waiting to finish prepare job..." << std::endl;
        std::thread time_out_counter {counter_job, 8000};
        time_out_counter.detach();
        try {
            fut.get();
            std::cout << "Ready to run post task..." << std::endl;
        }
        catch(std::future_error& err) {
            std::cout << "Error : " << err.what() << std::endl;
        }
        std::cout << "End of post job..." << std::endl;
    };

    std::promise<void> prom {};
    auto fut = prom.get_future();
    std::thread prepare_thread {prepare_job, std::move(prom)};
    std::thread post_thread {post_job, std::move(fut)};

    std::cout << "Waiting to join sub-threads..." << std::endl;
    prepare_thread.join();
    post_thread.join();

    std::cout << "End of this program..." << std::endl;
    return 0;
}
