//  Author  :   Gu-hwan Bae
//  Date    :   2 December, 2018
//  Summary :   Test modules for bind_variadic_args.cc

#ifndef TEMPLATE_FUNCS_H_
#define TEMPLATE_FUNCS_H_

#include <iostream>

namespace utils {

template <class Token>
void print_impl(Token&& token) {
    std::cout << token << ' ';
}

template <class Token, class... Args>
void print_impl(Token&& token, Args&&... args) {
    std::cout << token << ' ';
    print_impl(std::forward<Args>(args)...);
}

template <class... Args>
void print(Args&&... args) {
    print_impl(std::forward<Args>(args)...);
    std::cout << std::endl;
}

}  // namespace utils

#endif  // TEMPLATE_FUNCS_H_
