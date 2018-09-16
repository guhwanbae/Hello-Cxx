//  Author  :   Gu-hwan Bae
//  Date    :   16 September, 2018
//  Summary :   Choose suit function in compile time. Select to optimize forward constructor template -
//              when not calling copy or move constuructor.

#include <iostream>
#include <string>
#include <type_traits> // std::enable_if, std::is_same, std::is_base_of, std::decay

using namespace std;

class person {
    public :
        // since C++14
        template <typename T>
        using enable_if_not_person_type = enable_if_t<!is_base_of<person, decay_t<T>>::value>;
        
        // since C++14 (type traits helper : e.g, decay_t)
        //template <typename T>
        //using enalbe_if_not_person_type = enable_if_t<!is_same<person, decay_t<T>>::value>;

        template <typename T, typename = enable_if_not_person_type<T>>
        explicit person(T&& name) : n{forward<T>(name)} {
            cout << "Perfect forwarding constructor. parameter : " << n << endl;
        }
        
        explicit person(const person& oth) {
            n = oth.n;
            cout << "Copy constructor. name : " << n << endl;
        }
        explicit person(person&& oth) {
            n = move(oth.n);
            cout << "Move constructor. name : " << n << endl;
        }

        person& operator=(const person& oth) {
            n = oth.n;
            cout << "Copy assign operator. name : " << n << endl;
            return *this;
        }
        person& operator=(person&& oth) {
            if(this != &oth) {
                n = move(oth.n);
            }
            cout << "Move assign operator. name : " << n << endl;
            return *this;
        }
    private :
        string n;
};

int main() {
    person ryan {"Ryan"};
    person muzi {string{"Muzi"}};

    string jay_z_name {"Jay-Z"};
    person jay_z {jay_z_name};

    person clone_ryan {ryan};
    person clone_muzi {person{"Muzi"}};

    return 0;
}
