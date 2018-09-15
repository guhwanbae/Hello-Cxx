#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std::chrono;

void fill_as_randvals(std::vector<int>& seq, const int lower, const int upper) {
    auto begin = high_resolution_clock::now();

    std::random_device seed;
    std::mt19937 engine(seed());
    //std::mersenne_twister_engine engine(seed());
    std::uniform_int_distribution<> uniform_dist(lower, upper);

    for(auto it=seq.begin(); it!=seq.end(); ++it) {
        *it = uniform_dist(engine);
    }

    auto end = high_resolution_clock::now();
    std::cout << "Fill a vector with random numbers : " 
        << duration_cast<milliseconds>(end-begin).count() << "ms" << std::endl;
}

void calc_by_accumulate(const std::vector<int>& seq) {
    auto begin = high_resolution_clock::now();
    auto sum = std::accumulate(seq.begin(),seq.end(),0LL);
    auto end = high_resolution_clock::now();
    std::cout << "Accumulate sequence elements by using std::accumulate : " 
        << duration_cast<milliseconds>(end-begin).count() << " ms" << std::endl;
    std::cout << "Accumulate sequence elements by using std::accumulate : sum = "
        << sum << std::endl;
}

void calc_by_manual_cycle(const std::vector<int>& seq) {
    auto begin = high_resolution_clock::now();
    long long int sum {0};
    for(auto it=seq.begin(); it!=seq.end(); ++it) {
        sum += (*it);
    }
    auto end = high_resolution_clock::now();
    std::cout << "Accumulate sequence elements by looping manually : " 
        << duration_cast<milliseconds>(end-begin).count() << " ms" << std::endl;
    std::cout << "Accumulate sequence elements by looping manually : sum = "
        << sum << std::endl;
}

int main() {
    constexpr std::size_t len = 100000000;
    std::vector<int> seq(len);

    fill_as_randvals(seq, 0, 10);

    calc_by_manual_cycle(seq);
    calc_by_accumulate(seq);

    return 0;
}
