#include <iostream>

#include "movie.h"

enum class Genre {
    Art,
    Action,
    Drama,
};

Movie makeMovie(Genre gen) {
    switch(gen) {
        case Genre::Art : {
            Movie grand_budapest;
            grand_budapest.add_character({"Zero", "Lobby boy", 17});
            grand_budapest.add_character({"Gustav", "Concierges", 42});
            grand_budapest.add_character({"Madame D", "Countess", 87});
            return grand_budapest;
            break;
        }
        case Genre::Action : {
            Movie tajja;
            tajja.add_character({"Kim Gon", "Gambler", 27});
            tajja.add_character({"Madame Jeong", "Planner", 37});
            return tajja;
            break;
        }
        default : {
            Movie forest_gump;
            forest_gump.add_character({"Forest Gump", "President of Bubba Gump Co.", 40});
            return forest_gump;
            break;
        }
    }
}

void print_characters(const Movie::Characters& chs) {
    for(const auto& ch : chs) {
        cout << "name : " << ch.name << endl;
        cout << "job : " << ch.job << endl;
        cout << "age : " << ch.age << endl;
    }
}

void foo() {
    Movie the_simpsons;
    the_simpsons.add_character({"Homer Simpson", "Nuclear technician", 40});
    the_simpsons.add_character({"Clancy Wiggum", "Police Chief", 42});

    print_characters(the_simpsons.get_characters());
    print_characters(makeMovie(Genre::Art).get_characters());
}

int main() {
    foo();
    return 0;
}
