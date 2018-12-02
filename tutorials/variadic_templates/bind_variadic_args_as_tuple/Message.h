//  Author  :   Gu-hwan Bae
//  Date    :   2 December, 2018
//  Summary :   Binding variadic arguments to std::tuple. If a argument is rvalue, binding by copying.
//              Or if is lvalue, binding by reference.

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>
#include <functional>
#include <tuple>
#include <utility>

#include "TemplateFuncs.h"

class Message {
public :
    Message() {
        std::cout << "Message() : Hello!" << std::endl;
    }

    ~Message() {
        lazy_task_();
        std::cout << "~Message() : Bye!" << std::endl;
    }

    template <class... Args>
    void set_lazy_msg(Args&&... args) {
        auto tup = std::forward_as_tuple("The lazy message : ", args...);
        lazy_task_ = [this, pack = tup]() {    this->adapt_print(pack);    };
        utils::print("The original message : ", std::forward<Args>(args)...);
    }

private :
    std::function<void()> lazy_task_;

    template <class Tuple, std::size_t... Idx>
    void adapt_print_impl(Tuple&& tup, std::index_sequence<Idx...>) {
        utils::print(std::get<Idx>(std::forward<Tuple>(tup))...);
    }

    template <class Tuple>
    void adapt_print(Tuple&& tup) {
        adapt_print_impl(std::forward<Tuple>(tup),
            std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
    }
};

#endif  // MESSAGE_H_
