//  author  :   Gu-hwan Bae
//  date    :   June 17, 2018

// Copy object of custom class. 
// Implement copy constructor and copy operator.

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
    private:
        std::array<int, 2> dim; // # of rows = dim[0], # of cols = dim[1]
        T* elem;    // T type이고, dim[0]*dim[1]개의 원소를 갖는 포인터
};

// Class initializing을 통해 객체는 초기화 된다.
// 초기화된 객체에 값을 할당한다. 따라서 초기화 과정 필요없이 단순히 값을
// 대입하는 uninitialized_copy() 를 활용한다.
template <typename T>
Matrix::Matrix(const Matrix& rhs) : dim{rhs.dim}, elem{new T[rhs.size()]} {
    std::uninitialized_copy(rhs.elem, rhs.elem+rhs.size(), elem);
}

// Copy operator, 대입 연산자는 새로운 객체를 생성하고,
// 그 값을 복사될 값으로 할당한다.
template <typename T>
Matrix& Matrix::operator=(const Matrix& rhs) {
    if(dim[0] != rhs.dim[0] || dim[1] != rhs.dim[1]) {
        throw "bad size in Matrix=";
    }
    std::copy(rhs.elem, rhs.elem+rhs.size(), tmp.elem);
}
