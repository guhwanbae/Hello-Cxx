/*
 *  author  :   Gu-hwan Bae
 *  date    :   April 16, 2018
 */

#include <iostream>
#include <vector>
#include <algorithm>

void foo() {
    std::vector<int> v;
    for(int i=0; i<10; ++i) {
        v.push_back(i);
    }
    std::for_each(v.begin(), v.end(), 
            [] (int x) { 
            std::string numtype {};
            (x % 2 == 0) ? (numtype = "even") : (numtype = "odd");
            std::cout << x << " is " << numtype << "." << std::endl;
            }
            );
}

int main(int argc, char* argv[]) {
    foo();
    return 0;
}
