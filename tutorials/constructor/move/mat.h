//  author  :   Gu-hwan Bae
//  date    :   June 17, 2018

// Move object of custom class. 
// Implement move constructor and move operator.

#include <array>    //  std::array
#include <algorithm>    // std::copy
#include <memory>   // std::uninitialized_copy

template <typename T>
class Matrix {
    public:
        Matrix(int nrows, int ncols) : dim{nrows, ncols}, elem{new T[nrows*ncols]} {}
        ~Matrix { delete[] elem; }
        int size() const { return dim[0]*dim[1]; }
        
        Matrix(const Matrix&);
        Matrix& operator=(const Matrix&);

        Matrix(Matrix&&);
        Matrix& operator=(Matrix&&);

        Matrix operator+(const Matrix&, const Matrix&); // 두 Matrix를 합하고, 새로운 Matrix를 반환.
    private:
        std::array<int, 2> dim; // # of rows = dim[0], # of cols = dim[1]
        T* elem;    // T type이고, dim[0]*dim[1]개의 원소를 갖는 포인터
};

template <typename T>
Matrix::Matrix(const Matrix& rhs) : dim{rhs.dim}, elem{new T[rhs.size()]} {
    std::uninitialized_copy(rhs.elem, rhs.elem+rhs.size(), elem);
}

template <typename T>
Matrix& Matrix::operator=(const Matrix& rhs) {
    if(dim[0] != rhs.dim[0] || dim[1] != rhs.dim[1]) {
        throw "bad size in Matrix=";
    }
    std::copy(rhs.elem, rhs.elem+rhs.size(), tmp.elem);
}

// Perfect forwarding, 새로 생성된 객체는 rhs의 reference를 모두 가져온다.
// rhs 객체는 기본값을 가지며, 소멸자에 의해 자원을 반환한다.
template <typename T>
Matrix::Matrix(Matrix&& rhs) : dim{rhs.dim}, elem{rhs.elem} {
    rhs.dim = {0, 0};
    rhs.elem = nullptr;
}

// 단순히 두 값을 바꿔치는 것이다. 바꿔진 객체는 rvalue가 되는데, 
// 참조하는 객체가 없다면 소멸자에 의해 자원을 반환하게 된다.
template <typename T>
Matrix& Matrix::operator=(Matrix&& rhs) {
    std::swap(dim, rhs.dim);
    std::swap(elem, rhs.elem);
    return *this;
}

// Matrix를 합하는 연산은 꽤 비싼 연산이다.
// 또한 값에 의한 반환을 하고 있음을 잘 보자.
Matrix operator+(const Matrix& a, const Matrix& b) {
    if(a.dim[0] != b.dim[0] || a.dim[1] != b.dim[1]) {
        throw "unequal Matrix size in +";
    }
    Matrix ret{a.dim[0], a.dim[1]};
    constexpr int n {a.size()};
    for(int i = 0; i != n; ++i) {
        ret.elem[i] = a.elem[i] + b.elem[i];
    }
    // Matrix가 이동 생성자를 갖고 있으므로 외부에서 ret 객체를 받는 과정은
    // 암묵적으로 컴파일러에 의해 이동 연산으로 처리된다.
    return ret;
}
