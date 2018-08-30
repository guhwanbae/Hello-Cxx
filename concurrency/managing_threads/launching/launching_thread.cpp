/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   29 August, 2018
 *  Summary :   Passing functor, function pointer, lambda expr to
 *              std::thread and launching.
 */

#include <iostream>
#include <thread>

class Task
{
public :
    void operator()() const
    {
        std::cout << "Task::begin\n";
        hello();
        bye();
        std::cout << "Task::end\n";
    }
private :
    void hello() const { std::cout << "hello\n"; }
    void bye() const { std::cout << "bye\n"; }
};

void hello()
{
    std::cout << "hello\n";
}

void bye()
{
    std::cout << "bye\n";
}

void task_function()
{
    std::cout << "task_function() begin\n";
    hello();
    bye();
    std::cout << "task_function() end\n";
}

void foo()
{
    std::thread t1 {Task{}};
    std::thread t2 {task_function};
    auto job1 = [](){ std::cout << "hello\n"; };
    auto job2 = [](){ std::cout << "bye\n"; };
    std::thread t3 {[job1, job2]() {
        std::cout << "task_lambda begin\n";
        job1();
        job2();
        std::cout << "task_lambda end\n";
    }};
    t1.join();
    t2.join();
    t3.join();
}

int main()
{
    foo();
    return 0;
}
