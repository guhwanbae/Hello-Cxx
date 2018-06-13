/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 13, 2018
 */

// Pass arguments to class constructor or function parameter by initializer_list.
// initializer_list를 사용하여 클래스 생성자를 호출하거나, 함수의 인자로 전달한다.

#include <iostream>
#include <initializer_list>
#include "sequence.h"

// initilizer_list는 시퀀스로서 인덱스[]로 접근할 수 있다.
// 하지만 권장되는 방법은 아니다.
template <typename T>
void foo1(const std::initializer_list<T>& args) {
    std::cout << ">> Using index operator." << std::endl;
    for(int i = 0; i != args.size(); ++i) {
        std::cout << args.begin()[i] << '\n';
    }
}

// 다른 STL container처럼 iterator interface를 이용하여 요소에 접근할 수 있다.
template <typename T>
void foo2(const std::initializer_list<T>& args) {
    std::cout << ">> Using iterator interface." << std::endl;
    for(auto iter = args.begin(); iter != args.end(); ++iter) {
        std::cout << *iter << '\n';
    }
}

// iterator interface(begin, end)가 명시되어 있으므로, based for loop를 사용할 수 있다.
// 코드를 더 직관적으로 표현할 수 있다.
template <typename T>
void foo3(const std::initializer_list<T>& args) {
    std::cout << ">> Using based for loop." << std::endl;
    for(const auto& elem : args) {
        std::cout << elem << '\n';
    }
}

int main() {
    // 함수의 인자를 initializer_list로 전달한다.
    // foo1({0.1, 0.2});
    foo2({2, 3, 5, 7, 11});
    // 아래 코드는 double, int가 섞여있으므로 template type 추론에 실패한다.
    // foo({1, 2, 3.456});
    foo2({"Python", "Go language", "Ruby"});

    foo3({1.0 , 1.5, -2.14, 9.77, 0.99});
    foo3({"Java", "C++", "C++", "SmallTalk", "C#"});

    // 클래스 생성자에게 initializer_list를 넘겨주고 초기화한다.
    std::cout << ">> Initialize class object by initializer_list" << std::endl;
    Sequence<double> points {0.05, 0.17, 2.1, 1.15, -0.92, 9.00};
    points.traverse();

    return 0;
}
