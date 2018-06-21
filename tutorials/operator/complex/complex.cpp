//  author  :   Gu-hwan Bae
//  date    :   June 20, 2018

//  Using move sementics for large objects.
//  이동 연산을 활용하여 대규모 객체 이동의 효율을 높인다.
//  대규모 객체에 대한 연산자를 오버라이딩 할 때,
//  연산의 결과값으로 새로운 객체를 생성하게 되는데
//  이동 연산을 통해 불필요한 복사과정을 생략하고
//  프로그램의 성능을 높일 수 있다.

//  사실 이 Complex 클래스는 두 개의 double 기본 타입 변수를
//  가지므로 대규모 객체 이동에 적합한 예제는 아니다.
//  이동 연산이 어떻게 이루어지는지 각 생성자와 연산자 정의부분에
//  명시적인 출력을 하여 관찰하는데 의미를 두자.


#include <iostream>
#include <algorithm>

class Complex {
    public:
        Complex(double realNum ={}, double imagNum ={}) : \
            rm{realNum}, im{imagNum} {
                std::cout << "Constructor\n";
            };
        Complex(const Complex& comp) : rm{comp.rm}, im{comp.im} {
            std::cout << "Copy constructor\n";
        };
        Complex(Complex&& comp) : rm{comp.rm}, im{comp.im} {
            std::cout << "Move constructor\n";
            comp.rm = {};
            comp.im = {};
        };

        Complex& operator=(const Complex& comp) {
            std::cout << "Copy operator\n";
            if(this == &comp) {
                return *this;
            }
            rm = comp.rm;
            im = comp.im;
            return *this;
        }

        Complex& operator=(Complex&& comp) {
            rm = comp.rm;
            im = comp.im;
            comp.rm = 0.0;
            comp.im = 0.0;
            std::cout << "Move operator" << std::endl;
            
            return *this;
        }

        Complex& operator+=(const Complex& comp) {
            rm += comp.rm;
            im += comp.im;
            return *this;
        }

        double real() const {
            return rm;
        }
        double imag() const {
            return im;
        }
    private:
        double rm;
        double im;
};

/*
Complex operator+(const Complex& lhs, const Complex& rhs) {
    Complex ret {lhs};
    ret += rhs;
    return ret;
}*/

Complex&& operator+(const Complex& lhs, const Complex& rhs) {
    std::cout << "in binary operator+::";
    Complex ret {lhs};
    ret += rhs;
    return std::move(ret);
}

std::ostream& operator<<(std::ostream& os, const Complex& comp) {
    os << "-----------------------------------\n" \
        << "Real : " << comp.real() << "\n" \
        << "Imag : " << comp.imag() << "\n";
    return os;
}

int main() {
    //Complex origin {};
    //std::cout << origin;

    Complex source {5.0, 5.0};
    Complex target {3.5, -0.75};

    Complex point = source + target;
    std::cout << point;

    Complex point2 {};
    point2 = Complex{1.2, 2.3} + Complex{6.5, 5.4};
    std::cout << point2;

    return 0;
}
