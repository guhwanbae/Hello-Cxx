//  Author  :   Gu-hwan Bae
//  Date    :   15 September, 2018
//  Summary :   Synchronize two tasks downloader and player by using std::promise and std::future.

#include <iostream>
#include <thread>
#include <future>
#include <chrono>

class received_data {
    public :
        received_data(const std::string& name) : n{name} {}
        std::string get_data_name() const {
            return n;
        }
    private :
        std::string n;
};

class play_data {
    public :
        void operator()(std::future<received_data>&& fut) {
            std::cout << "Player : Waiting for download..." << std::endl;
            auto recv_data = fut.get();
            std::cout << "Player : Data has been successfully received!" << std::endl;
            std::cout << "Player : Start playing - " << recv_data.get_data_name() << std::endl;
        }
};

class download_data {
    public :
        void operator()(std::promise<received_data>&& prom, const std::string& data_name) {
            std::cout << "Downloader : Downloading data from network..." << std::endl;
            for(int cnt=0; cnt<=100; cnt+=25) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "Downloader : " << cnt << "% received..." << std::endl;
            }
            prom.set_value(received_data{data_name});
        }
};

void download_and_play(const std::string& data_name) {
    std::promise<received_data> prom;
    std::future<received_data> fut = prom.get_future();

    std::thread downloader(download_data{}, std::move(prom), data_name);
    std::thread player(play_data{}, std::move(fut));

    downloader.join();
    player.join();
}

int main() {
    download_and_play("The Great Gatsby");
    
    std::cout << "End of this program." << std::endl;
}
