//  Author  :   Gu-hwan Bae
//  Date    :   16 September, 2018
//  Summary :   Compare calculation approach.
//              Single threading std::accumulate vs Parallel threading accumulate.
//              In addition, measurements by adjusting compiler optimization option were also compared.

#include <iostream>
#include <algorithm>
#include <future>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

template <typename InputIt, typename T>
T parallel_accumulate(InputIt first, InputIt last, T init) {
    static constexpr int min_size {1000000};
    const auto input_size = distance(first, last);
    const auto num_tasks = (input_size < min_size) ? 1 : thread::hardware_concurrency();
    const size_t chunk_size = input_size / num_tasks;

    vector<future<T>> futures;
    for(size_t i=0; i<num_tasks; ++i) {
        futures.emplace_back(async(launch::async, [first, chunk_size]() {
            return accumulate(first, next(first, chunk_size), T {});
        }));
        advance(first, chunk_size);
    }
    
    for(auto& fut : futures) {
        init += fut.get();
    }
    return init;
}

template <typename It>
void calc_by_parallel_accumulate(It first, It last) {
    auto begin = high_resolution_clock::now();
    auto sum = parallel_accumulate(first,last,0);
    auto end = high_resolution_clock::now();
    cout << "Accumulate sequence elements by using parallel_accumulate(multi thread) : " 
        << duration_cast<milliseconds>(end-begin).count() << " ms" << endl;
    cout << "Accumulate sequence elements by using parallel_accumulate(multi thread) : sum = "
        << sum << endl;
}

template <typename It>
void calc_by_accumulate(It first, It last) {
    auto begin = high_resolution_clock::now();
    auto sum = accumulate(first,last,0);
    auto end = high_resolution_clock::now();
    cout << "Accumulate sequence elements by using std::accumulate(single thread) : " 
        << duration_cast<milliseconds>(end-begin).count() << " ms" << endl;
    cout << "Accumulate sequence elements by using std::accumulate(single_thread) : sum = "
        << sum << endl;
}

template <typename It>
void fill_as_randvals(It first, It last, const int lower, const int upper) {
    auto begin = high_resolution_clock::now();

    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution<> uniform_dist(lower, upper); //Mersenne Twister Engine

    for(auto it=first; it!=last; ++it) {
        *it = uniform_dist(engine);
    }

    auto end = high_resolution_clock::now();
    cout << "Fill a vector with random numbers : " 
        << duration_cast<milliseconds>(end-begin).count() << "ms" << endl;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage : " << argv[0] << " -option" << endl
             << "        -s --single" << endl
             << "        -p --parallel" << endl;
        return -1;
    }

    string option {argv[1]};
    if(option != "-s" && option != "--single" &&
       option != "-p" && option != "--parallel") {
        cout << "Invalid option!" << endl;
        return -1;
    }
    
    constexpr size_t len = 100000000;
    vector<int> seq(len);

    fill_as_randvals(seq.begin(), seq.end(), 0, 10);

    if(thread::hardware_concurrency() == 1) {
        cout << "It is single-processor system. :(" << endl;
    }
    else {
        cout << "It is multi-processor system. :)" << endl;
    }

    if(option == "-p" || option == "--parallel") {
        calc_by_parallel_accumulate(seq.begin(), seq.end());
    }
    else {
        calc_by_accumulate(seq.begin(), seq.end());
    }

    return 0;
}
