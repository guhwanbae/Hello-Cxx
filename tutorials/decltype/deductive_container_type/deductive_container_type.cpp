/*
 * Author   :   Gu-hwan Bae
 * Date     :   August 13, 2018
 */

#include <iostream>
#include <vector>

// C++14
template <typename Container, typename Index>
decltype(auto)
element_cxx14(Container&& c, Index i)
{
    return std::forward<Container>(c)[i];
}

// C++11
template <typename Container, typename Index>
auto
element_cxx11(Container&& c, Index i)
-> decltype(std::forward<Container>(c)[i])
{
    return std::forward<Container>(c)[i];
}

int main() {
    std::vector<int> iv(5, 1);
    // Return type is int.
    std::cout << element_cxx14(iv, 3) << std::endl;

    // Return type is const std::string.
    std::vector<const std::string> sv {"fox", "rabbit", "lamb", "dog"};
    std::cout << element_cxx11(sv, 0) << std::endl;

    const double palomenso {"0.1125"};
    auto x {palomenso}; // Type of x is double.
    decltype(auto) y {palomenso};   // Type of y is const double.

    return 0;
}
