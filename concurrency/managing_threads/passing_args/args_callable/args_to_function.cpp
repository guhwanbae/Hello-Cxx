/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   29 August, 2018
 *  Summary :   Pass correctly supplied values as reference by using std::ref.
 */

#include <iostream>
#include <thread>
#include <string>

// void job(std::string& msg)
void job(std::string msg)
{
    msg = "bye";
}

void foo()
{
    std::string token {"hello"};
    // std::thread t(job, std::ref(token));
    std::thread t(job, token);
    /*
        std::thread ctor doesn't know type of job function arguments.
        so blindly copies the supplied values.
        If you wanna pass a refrence to internal std::thread,
        use the std::ref.
        It makes correctly passing a reference to job function.
    */
    t.join();
    std::cout << "token : " << token << std::endl;
}

int main()
{
    foo();
    return 0;
}
