/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   29 August, 2018
 *  Summary :   Transferring ownership of a thread to 'scoped_thread' class.
 *              It's ensuring thread are completed before a scope is exited.
 */

#include <iostream>
#include <thread>

class scoped_thread
{
public :
    // Transferring ownership of argument to internal thread object.
    explicit scoped_thread(std::thread&& thread) : t{std::move(thread)}
    {
        if(!t.joinable()) {
            throw std::logic_error("No thread.");
        }
    }
    ~scoped_thread()
    {
        t.join();
        std::cout << "scoped_thread : successfully joined." << std::endl;
    }

    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator=(const scoped_thread&) = delete;
private :
    std::thread t;
};
