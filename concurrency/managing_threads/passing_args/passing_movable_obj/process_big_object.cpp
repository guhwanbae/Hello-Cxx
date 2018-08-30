/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   29 August, 2018
 *  Summary :   Transfer ownership of 'big_object' 
 *              to internal storage of newly created thread.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>
#include <thread>

// C++14
class big_object
{
public :
    big_object(int size = {4096}) : \
        signals { std::move(std::vector<double>(size, 0)) } {}
    ~big_object() { std::cout << "~big_object()" << std::endl; }

    void increment_each(const double step) noexcept
    {
        std::for_each(signals.begin(), signals.end(), \
            [this,step](auto& elem) { elem += step; });
    }
    double sum() const
    {
        return std::accumulate(signals.begin(), signals.end(), 0.0);
    }
private :
    std::vector<double> signals;
};

void foo()
{   
    // std::unique_ptr<> can't be copied but can only be moved.
    auto pObj = std::make_unique<big_object>();
    pObj->increment_each(1.1);
    std::cout << pObj->sum() << std::endl;

    auto process_big_object = \
        [](std::unique_ptr<big_object> pObj) { \
        pObj->increment_each(2.2); \
        std::cout << pObj->sum() << std::endl; \
        pObj->increment_each(3.3); \
        std::cout << pObj->sum() << std::endl; \
        // lambda will not return unique_ptr of big_object.
        // big_object will be destroyed when this lambda exit.
        std::cout << "End of process_big_object()." << std::endl; };
    
    // Using std::move, Explicitly transfer ownership of big_object.
    // big_object is transferred first into internal storage for std::thread
    // and then into process_big_object(lambda).
    std::thread t(process_big_object, std::move(pObj));
    t.join();
    std::cout << "End of foo()." << std::endl;
}

int main()
{
    foo();
    std::cout << "End of this program." << std::endl;
    return 0;
}
