//  Author  :   Gu-hwan Bae
//  Date    :   16 October, 2018
//  Summary :   Function call binding depends on whether it is 
//              dependent or independent of the template argument.

#include <iostream>

class English {
    public :
        void hello() const { std::cout << "Hello!" << std::endl; }
};

class French {
    public :
        void hello() const { std::cout << "Bonjour!" << std::endl; }
};

class Korean {
    public :
        void hello() const { std::cout << "안녕하세요!" << std::endl; }
};

void default_say_hello() {
    std::cout << "Hello, World!" << std::endl;
}

// Calling lang.hello() is dependent on the template argument 'Language'.
// So, 'lang.hello()' is bound when calling say_hello(Language).
template<typename Language>
void say_hello(Language lang) {
    lang.hello();
    default_say_hello();  // Calling default_say_hello() is independent
                          // of the template argument 'Language'.
                          // So, 'default_say_hello() is bound
                          // when the compiler defines this.
}

void test_say_hello() {
    say_hello(English {});  // Here, say_hello(Language) is instanced by 'English' type.
    say_hello(French {});  // Here, say_hello(Language) is instanced by 'French' type.
    say_hello(Korean {});  // Here, say_hello(Language) is instanced by 'Korean' type.
}

int main() {
    test_say_hello();
    return 0;
}
