//  Author  :   Gu-hwan Bae
//  Date    :   15 September, 2018
//  Summary :   Handle a exception from dividing by zero in divides task. 
//              std::future and std::promise approach allows handling exceptions -
//              in task and receiver respond to them.

#include <iostream>
#include <thread>
#include <future>
#include <exception>
#include <string>

using namespace std;

class divides_num_den {
    public :
        void operator()(promise<double>&& prom, int num, int den) {
            try {
                if(den == 0) {
                    throw runtime_error("Numeric exception! Divide by zero.");
                }
                prom.set_value(static_cast<double>(num)/den);
            }
            catch(...) {
                prom.set_exception(current_exception());
            }
        }
};

void divider(int num, int den) {
    promise<double> prom;
    auto fut = prom.get_future();
    
    thread divide_task(divides_num_den {}, move(prom), num, den);
    try {
        cout << "Divider : " << num << '/' << den << " = " << fut.get() << endl;
    }
    catch(runtime_error& excpt) {
        cout << excpt.what() << endl;
    }

    divide_task.join();
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "Usage : " << argv[0] << " numerator denominator" << endl;
        return -1;
    }
    
    int num {0}, den {0};
    try {
        num = stoi(string{argv[1]});
        den = stoi(string{argv[2]});
    }
    catch(invalid_argument& excpt) {
        cout << "Numerator or denominator is not a interger. " << excpt.what() << endl;
        return -1;
    }

    divider(num, den);

    return 0;
}
