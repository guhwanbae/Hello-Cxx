#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Character {
    string name;
    string job;
    int age;
};

class Movie {
public :
    using Characters = vector<Character>;

    void add_character(const Character& c);
    Characters& get_characters() &;
    Characters&& get_characters() &&;
private :
    vector<Character> chs;
};
