/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   29 August, 2018
 *  Summary :   Using RAII to wait for a thread to complete.
 */

#include <iostream>
#include <thread>

class thread_handle
{
public :
    explicit thread_handle(std::thread& thread) : t{thread} {}
    ~thread_handle()
    {
        // join() can be called only once for a given thread of execution. 
        if(t.joinable())
        {
            t.join();
            std::cout << "successfully joined in thread_handle dtor." << std::endl;
        }
    }
    // Stop from copying or assigning.
    thread_handle(const thread_handle&) = delete;
    thread_handle& operator=(const thread_handle&) = delete;
private :
    std::thread& t;
};

void do_something_in_current_thread()
{
    throw "oops! something wrong.";
}

void foo()
{
    int parameter {2018};
    std::thread t {[parameter]() {  // capture a loacal value as copy.
        std::cout << "argument : " << parameter << std::endl;
    }};
    // thread_handle'll be destroyed 
    // when this fucntion normal or expectional exit.
    thread_handle h{t};

    try
    {
        // Exception might be invoked under tasks.
        do_something_in_current_thread();
    }
    catch(const char* msg)
    {
        std::cout << msg << std::endl;
    }
}

int main()
{
    foo();
    std::cout << "End of this program." << std::endl;
    return 0;
}
