//  Author  :   Gu-hwan Bae
//  Date    :   8 October, 2018
//  Summary :   Example of how to use the nested dependent type.
//              Use the 'typename' keyword to tell the compiler 
//              that this token is a type(not a variable!).

#include <iostream>
#include <vector>
#include <list>
#include <array>

// Return type and it var type are const_iterator. 
template <typename Cont>
typename Cont::const_iterator find_negative_num(const Cont& c) {
    // Use std::cbegin and std::cend to receive array type as well as sequence container.
    // std::cbegin and std::cend can be used since C++ 14.
    typename Cont::const_iterator it = std::cbegin(c);
    for (; it != std::cend(c); ++it) {
        if (*it < 0) {
            std::cout << "Negative number is " << *it << std::endl;
            break;
        }
    }
    if(it == std::cend(c)) std::cout << "Not found!" << std::endl;
    return it;
}

// Or you can use 'auto' keyword to infer.
template <typename Cont>
decltype(auto) find_negative_num_use_auto(const Cont& c) {
    auto it = std::cbegin(c);
    for(; it != std::cend(c); ++it) {
        if(*it < 0) {
            std::cout << "Negative number is " << *it << std::endl;
            break;
        }
    }
    if(it == std::cend(c)) std::cout << "Not found!" << std::endl;
    return it;
}

void test_find_negative_num() {
    std::vector<int> primes {2, 3, 5, 7, 9, 11, -13, 17};
    std::list <double> rates_of_growth {0.22, 0.31, 0.45, 0.47, -0.08, 0.15};
    std::array<int, 5> personal_days {8, 9, 10, 11, 12};

    find_negative_num(primes);
    find_negative_num(rates_of_growth);
    find_negative_num(personal_days);

    find_negative_num_use_auto(primes);
    find_negative_num_use_auto(rates_of_growth);
    find_negative_num_use_auto(personal_days);
}

int main() {
    test_find_negative_num();
    return 0;
}
