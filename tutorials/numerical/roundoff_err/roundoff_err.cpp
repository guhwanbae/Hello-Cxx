/*
 *  author  :   Gu-hwan Bae
 *  date    :   April 23, 2018
 */

#include <iostream>

int main(int argc, char* argv[]) {
    float x {1.0f/333};
    float sum {0};

    for(int i=0; i<333; ++i) {
        sum += x;
    }
    std::cout << "sum = " << sum << " and x = " << x << std::endl;

    return 0;
}
