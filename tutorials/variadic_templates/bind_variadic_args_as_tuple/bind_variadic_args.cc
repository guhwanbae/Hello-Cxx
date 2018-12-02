//  Author  :   Gu-hwan Bae
//  Date    :   2 December, 2018
//  Summary :   Binding variadic arguments to std::tuple. If a argument is rvalue, binding by copying.
//              Or if is lvalue, binding by reference.
//              The method set_lazy_msg() of Message class captures variadic arguments by forwarding to
//              clojure object.

#include <iostream>
#include <string>

#include "Message.h"
#include "TemplateFuncs.h"

int main() {
    std::string verbose_1 {"Introduction to Linear Algebra"};
    std::string verbose_2 {"Oh! Lucky!"};
    int num_1 {777};
    double num_2 {3.14f}, num_3 {0.777f};

    Message msg {};
    msg.set_lazy_msg(verbose_1, verbose_2, std::string {"Las Vegas"}, num_1, num_2, num_3, 'z');

    verbose_1 = "Application from Linear Algebra";
    verbose_2 = "Yes! Lucky!";
    num_2 = 2.71828f;

    std::cout << "End of this program." << std::endl;
    return 0;
}
