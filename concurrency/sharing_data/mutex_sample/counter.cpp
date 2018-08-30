#include <iostream>
#include <thread>
#include <mutex>

class counter
{
public :
    counter(const int entry = {0}) : cnt{entry} {}

    void print() 
    {
        std::lock_guard<std::mutex> g(m);
        std::cout<<"count:"<<cnt<<std::endl;
    }

    void up()
    {
        std::lock_guard<std::mutex> g(m);
        ++cnt;
    }
    void down()
    {
        std::lock_guard<std::mutex> g(m);
        --cnt;
    }
private :
    int cnt;
    std::mutex m;
};


void foo()
{
    counter cnt;
    auto inc = [&cnt](const int n) { \
        for(int i=0;i<n;++i) { cnt.up(); } };
    auto dec = [&cnt](const int n) { \
        for(int i=0;i<n;++i) { cnt.down(); } };

    std::thread t_inc(inc, 1000000);
    std::thread t_dec(dec, 1000000);

    t_inc.join();
    t_dec.join();

    cnt.print();
}

int main()
{
    foo();
    return 0;
}
