/*
 * Author   :   Gu-hwan Bae
 * Date     :   August 13, 2018
 */

#include <iostream>
#include <vector>

// Type checker by using compiling error message.
template <typename T>
class TypeCheck;

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

int hf(const double r) { return 0; };

int main() {
    std::vector<int> iv(5, 1);
    // Return type is int &.
    TypeCheck<decltype(element_cxx14(iv, 3))> ivType;

    // Return type is const std::string (std::basic_string<char> &).
    std::vector<const std::string> sv {"fox", "rabbit", "lamb", "dog"};
    TypeCheck<decltype(element_cxx11(sv, 2))> svType;

    const double palomenso {0.1125};
    auto x {palomenso}; // Type of x is double.
    TypeCheck<decltype(x)> xType;
    decltype(auto) y {palomenso};   // Type of y is const double.
    TypeCheck<decltype(y)> yType;

    TypeCheck<decltype(hf)> hfType;
    TypeCheck<decltype(&hf)> hfrType;

    auto eq = [](const int x, const int y) { return (x==y); };
    TypeCheck<decltype(eq)> eqType;

    auto sum = [](const double x, const double y) -> double { return (x+y); };
    TypeCheck<decltype(sum)> sumType;

    return 0;
}
