/*
 *  author  :   Gu-hwan Bae
 *  date    :   May 10, 2018
 */

/* Find and parse zip code list using regular expression.
   C++ library regex와 정규표현식을 사용하여 
   Zip code text를 Parsing한다. */

#include <iostream>
#include <string>
#include <regex>
#include <fstream>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Invalid input." << std::endl;
        return -1;
    }
    const char* file_name = argv[1];

    std::ifstream in {file_name};
    if(!in) {
        std::cerr << "No mach file as \"" << file_name << "\"." << std::endl;
        return -1;
    }
    std::cout << "Open \"" << file_name << "\"." << std::endl;

    const std::string rexpat {R"(\w{2}\s*\d{5}(-\d{4})?)"};
    std::regex pat {rexpat};
    
    std::cout << "pattern: " << rexpat << std::endl;
    int line_num {0};
    for(std::string line; getline(in, line); ) {
        ++line_num;
        std::smatch matches;
        if(std::regex_search(line, matches, pat)) {
            std::cout << line_num << ": " << matches[0] << std::endl;
            if(matches.size() > 1 && matches[1].matched) {
                std::cout << "\t: " << matches[1] << std::endl;
            }
        }
    }

    return 0;
}
