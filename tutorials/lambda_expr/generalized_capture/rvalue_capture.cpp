//  Author  :   Gu-hwan Bae
//  Date    :   18 September, 2018
//  Summary :   Since C++14, Generalized lambda capture enable move rvalue into lambda class.
//              In C++11, You can simulate generalized lambda capture by using std::bind. 

#define CXX_14 1

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename It>
void print_sequence(It first, It last) {
    cout << "Sequence : ";
    for(It it = first; it != last; ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}

void do_something_cxx_11(const vector<int> sequence) { // C++11
    // It binds life-scope of sequence to bind object.
    // So, lambda receive a sequence data as reference.
    auto show = bind([](const vector<int>& seq)
        { print_sequence(seq.begin(), seq.end()); },
        move(sequence));
    show();
}

#if CXX_14
void do_something_cxx_14(vector<int> sequence) { // C++14
    // Generalized lambda capture is possible since C++14.
    // This enables capturing a rvalue type. 
    auto show = [seq = move(sequence)]() {
        print_sequence(seq.begin(), seq.end()); };
    show();
}
#endif

int main() {
    vector<int> primes {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    cout << "Until C++11..." << endl;
    do_something_cxx_11(primes);

#if CXX_14
    cout << "Since C++14..." << endl;
    do_something_cxx_14(primes);
#endif

    return 0;
}
