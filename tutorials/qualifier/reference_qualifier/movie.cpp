#include <iostream>

#include "movie.h"

using namespace std;

void Movie::add_character(const Character& c) {
    chs.push_back(c);
}

Movie::Characters& Movie::get_characters() & {
    cout << "get_characters()" << "return Characters&(lvalue)." << endl;
    return chs;
}

Movie::Characters&& Movie::get_characters() && {
    cout << "get_characters()" << "return Characters&&(rvalue)." << endl;
    return move(chs);
}
