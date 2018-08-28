//  Author  :   Gu-hwan Bae
//  Date    :   28 August, 2018
//  Summary :   Hetero-type tuple by using variadic templates.

#include <iostream>
#include <tuple>

// The variadic parameter 'Args' is called a 'parameter pack'.
// and the use of 'Args ...' is called a 'pack expansion'.
// sizeof...() return the number of elements in 'parameter pack' as constexpr.
template <typename ... Args>
class Package
{
public :
    Package(const Args& ... args) : \
        t{std::make_tuple(args ...)}, s{sizeof...(args)} {}

    void print_elements() const
    {
        std::cout << '(';
        for_each(t, [this](const auto& elem) {  std::cout << elem << ','; });
        std::cout << ")\n";
    }
private :
    // E.g) Package<int, char, string> 
    // tuple<int, char, string>
    std::tuple<Args ...> t;
    std::size_t s;
};
