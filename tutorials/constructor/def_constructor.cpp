#include <iostream>

class mcomplex {
    public :
        Complex(double r ={0}, double i ={0}) : re{r}, im{i} {};
    
        void show() {
            std::cout << "(" << re << ", "<< im << ")\n";
        }
    private :
        double re;
        double im;
};

int main() {
    Complex c1;
    c1.show();

    Complex c2 = {-3.5};
    c2.show();

    Complex c3 = {1.7, -0.105};
    c3.show();

    return 0;
}
