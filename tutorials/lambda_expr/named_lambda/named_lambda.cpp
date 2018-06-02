/*
 *  author  :   Gu-hwan Bae
 *  date    :   April 17, 2018
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> add_user() {
    std::vector<std::string> v;
    std::string user_name {};
    while(std::cin >> user_name && user_name != "q") {
        v.push_back(user_name);
    }
    return v;
}

void foo(std::vector<std::string> v) {
    auto print_users = [] (std::string user_name) { std::cout << "hellow " << user_name << std::endl; };
    std::for_each(v.begin(), v.end(), print_users);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> user_list = add_user();
    foo(user_list);

    std::cout << "End of this program." << std::endl;
    return 0;
}
