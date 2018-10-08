//  Author  :   Gu-hwan Bae
//  Date    :   8 October, 2018
//  Summary :   Use the 'typename' keyword for type obtained from type_traits class.
//              Becuase that type is dependent to template parameter of type_traits class.

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <array>

// C++ 11 Style
template <typename Iter>
auto get_value_from_iterator_cxx11(Iter it) -> typename std::iterator_traits<Iter>::value_type {
    typename std::iterator_traits<Iter>::value_type temp {*it};
    std::cout << "value from iterator : " << temp << std::endl;
    return temp;
}

// C++ 14 Style
template <typename Iter>
decltype(auto) get_value_from_iterator_cxx14(Iter it) {
    typename std::iterator_traits<Iter>::value_type temp {*it};
    std::cout << "value from iterator : " << temp << std::endl;
    return temp;
}

// C++ 11 Style with helper alias.
// 'std::iterator_traits<T>::value_type is long long type name.
// A simple alias can be created by using 'using' keyword.
template <typename T>
using elem_type_from_iter = typename std::iterator_traits<T>::value_type;

template <typename Iter>
auto get_value_from_iterator_use_helper_cxx11(Iter it) -> elem_type_from_iter<Iter> {
    elem_type_from_iter<Iter> temp {*it};
    std::cout << "value from iterator : " << temp << std::endl;
    return temp;
}

void test_get_value() {
    std::vector<int> primes {2, 3, 5, 7, 11};
    get_value_from_iterator_cxx11(primes.begin());
    get_value_from_iterator_cxx14(primes.begin() + 2);
    get_value_from_iterator_use_helper_cxx11(primes.begin() + 4);
}

int main() {
    test_get_value();
    return 0;
}