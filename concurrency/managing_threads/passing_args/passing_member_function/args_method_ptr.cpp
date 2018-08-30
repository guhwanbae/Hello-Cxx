#include <iostream>
#include <thread>

class Staff
{
public :
    void greetings(const std::string& name) const
    {
        std::cout << "welcome, " << name << std::endl; 
    }
};

void foo()
{
    Staff sally;
    std::string user_name {"Ryan"};
    // This cod will invoke sally.greetings() on the new thread.
    // Supplied object pointer(&sally) to std::thread ctor will be
    // the first argument to the member function and so forth.
    std::thread t(&Staff::greetings, &sally, std::ref(user_name));
    t.join();
}

int main()
{
    foo();
    return 0;
}
