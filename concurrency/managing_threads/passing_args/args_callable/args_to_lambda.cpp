/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   29 August, 2018
 *  Summary :   Pass correctly supplied values as reference by using std::ref.
 */

#include <iostream>
#include <thread>
#include <string>

void bar()
{
    auto job = [](int flag) { flag = 777; };
    int num {1};
    std::thread t(job, num);
    // pass a copy of flag to internal std::thread ctor. 
    // std::thread pass a supplied value(flag) to job lambda.
    t.join();
    // job lambda change a flag as 777. but bar::flag does not change.
    std::cout << "num : " << num << std::endl; // num is 1.
}

void foo()
{
    auto job = [](std::string& msg) { msg = "bye"; };
    std::string token {"hello"};
    std::thread t(job, std::ref(token));
    /*
       std::thread ctor doesn't know type of job function arguments.
       so blindly copies the supplied values.
       If you wanna pass a refrence to internal std::thread,
       use the std::ref.
       It makes correctly passing a reference to job function.
     */
    t.join();
    // job lambda change a msg(reference of foo::token) as 'bye'.
    std::cout << "token : " << token << std::endl; // token is 'bye'.
}

int main()
{
    bar();
    //foo();
    return 0;
}
