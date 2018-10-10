//  Author  :   Gu-hwan Bae
//  Date    :   10 October, 2018
//  Summary :   Creating a factorial struct in which all results are calculated
//              at compile-time by using TMP(template meta programming).

#include <iostream>

// Task that might be achived with iteration in ordinary programming
// have to be redefined in terms of recursion.
template <long long N>
struct Factorial {
    // Factorial<N>::value is computed and refers recursively itself.
    static constexpr long long value {N * Factorial<N-1>::value};
};

// Base condition of recursive template method and explicit template specialization.
template <>
struct Factorial<0> {
    // In order for this recurrence relation to be extended to n=0,
    // it is necessary to define as '!0 = 1'.
    static constexpr long long value {1};
};

void test_factorial() {
    // Without computations at run-time, it can be used as constants.
    std::cout << "factorial 5! = " << Factorial<5>::value << std::endl;
    std::cout << "factorial 10! = " << Factorial<10>::value << std::endl;
    std::cout << "factorial 15! = " << Factorial<15>::value << std::endl;
    std::cout << "factorial 0! = " << Factorial<0>::value << std::endl;

    // Oops! factorial 30! makes value variable(long long type) overflow.
    // But don't worry! Becuase compiler reports a overflow error,
    // you don't have to debug undefined behavior.
    std::cout << "factorial 30! = " << Factorial<30>::value << std::endl;
}

int main() {
    test_factorial();
    return 0;
}
