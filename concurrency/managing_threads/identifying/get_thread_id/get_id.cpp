#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <string>
#include <algorithm>
#include <mutex>

// C++11
void foo()
{
    using lockguard = std::lock_guard<std::thread>;
    std::mutex m_out;   // Sychronizing a printing sequence.

    std::vector<std::thread> lst;
    auto job = [&m_out](const std::string& name) { \
        lockguard g{m_out};
        std::cout<<"hello, "<<name<<". tid:"<<std::this_thread::get_id()<<'\n';
    }; 

    for(int i=0;i<20;++i)
    {
        lst.emplace_back(job,std::to_string(i));
    }

    std::for_each(lst.begin(),lst.end(), \
        std::mem_fn(&std::thread::join));

    std::cout<<"End of foo().\n";
}

int main()
{
    foo();
    return 0;
}
