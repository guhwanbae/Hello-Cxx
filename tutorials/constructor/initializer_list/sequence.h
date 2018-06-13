/*
 *  author  :   Gu-hwan Bae
 *  date    :   June 13, 2018
 */

#include <iostream>
#include <initializer_list>
#include <memory>   // reserve(), uninitialized_copy()

template <typename T>
class Sequence {
    public :
        Sequence(std::initializer_list<T> ls);
        ~Sequence();
        void traverse();
    private :
        int size;
        T* elem;
};

template <typename T>
Sequence<T>::Sequence(std::initializer_list<T> ls) : size{ls.size()} {
    elem = new T[size];
    std::uninitialized_copy(ls.begin(), ls.end(), elem);
}

template <typename T>
Sequence<T>::~Sequence() {
    delete[] elem;
}

template <typename T>
void Sequence<T>::traverse() {
    for(int i = 0; i < size; ++i) {
        std::cout << elem[i] << '\t';
    }
    std::cout << std::endl;
}
