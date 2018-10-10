//  Author  :   Gu-hwan Bae
//  Date    :   10 October, 2018
//  Summary :   How to choose appropriate code at compile-time?
//              Using function overloading and specialized template,
//              you can make sure that function optimized for each iterator
//              is selected at compile-time.

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>

template <typename Iter>
void do_something_worker(Iter it, std::random_access_iterator_tag) {
    std::cout << "This is worker for random access iterator." << std::endl;
    // do something with random access iterator.
}

template <typename Iter>
void do_something_worker(Iter it, std::bidirectional_iterator_tag) {
    std::cout << "This is worker for bidirectional iterator." << std::endl;
    // do something with bidirectional iterator.
}

template <typename Iter>
void do_something_worker(Iter it, std::forward_iterator_tag) {
    std::cout << "This is worker for forward iterator." << std::endl;
    // do something with forward iterator.
}

// do_something master fucntion.
template <typename Iter>
void do_something(Iter it) {
    // type traits class, iterator_category is determined at compile-time.
    do_something_worker(it, typename std::iterator_traits<Iter>::iterator_category());
}

void test_do_something() {
    std::vector<int> primes {2, 3, 5, 7, 11, 13};
    do_something(primes.begin());  // call function for random acess iterator.

    std::list<double> growth_ratio {2.2, 3.4, 3.0, 2.9, 3.5};
    do_something(growth_ratio.begin());  // call function for bidirectional iterator.

    std::unordered_map<int, std::string> main_events {
        {1991, "Soviet union disolved"},
        {1992, "My birthday"},
        {1994, "LG Twins win in KBL"},
        {1997, "IMF"} };
    do_something(main_events.begin());  // call function for forward iterator.
}

int main() {
    test_do_something();
    return 0;
}