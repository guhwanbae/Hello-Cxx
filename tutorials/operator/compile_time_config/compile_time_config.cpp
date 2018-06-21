//  author  :   Gu-hwan Bae
//  date    :   June 21, 2018

//  Provide constructors and accessors that is configured
//  at compile time.
//  생성자와 접근자를 상수화시켜서 컴파일 타임에 판단되도록 
//  할 수 있다.

#include <iostream>

class Complex {
public:
    constexpr Complex(double r =0, double i =0) : re{r}, im{i} {}
    constexpr double real() const { return re; }
    constexpr double imag() const { return im; }
private:
    double re;
    double im;
};

// Complex 객체가 매우 작고, 컴파일 타임에 초기화가 가능하므로,
// 아래와 같은 비교 연산을 큰 오버헤드 없이 표현할 수 있다.
inline bool operator==(Complex x, Complex y) {
    return (x.real() == y.real()) && (x.imag() == y.imag());
}

std::ostream& operator<<(std::ostream& os, Complex comp) {
    os << "Real : " << comp.real() << " Imag : " << comp.imag();
    return os;
}

int main() {
    // 생성자가 인라인으로 평가될만큼 간단하고 상수화 된 경우
    // 리터럴로 생성한 객체들은 컴파일 타임에 초기화 될 수 있다.
    Complex origin {};
    std::cout << origin << std::endl;
    // constexpr 키워드를 사용하여 명시적으로 컴파일 타임에 
    // 객체가 초기화 되도록 할 수 있다.
    constexpr Complex vp {381.05, -20.11};
    std::cout << vp << std::endl;

    return 0;
}
