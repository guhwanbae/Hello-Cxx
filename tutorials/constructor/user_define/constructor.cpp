//  author  :   Gu-hwan Bae
//  date    :   June 20, 2018

//  Define consturctor, copy constructor, move constructor,
//  copy operator, and move operator.

#include <iostream>
#include <string>
#include <algorithm>

class Tag {
    public :
        explicit Tag(const std::string& sr ={"RUVX6M"}, \
                const std::string& prod = {"Bavaria"}) : \
            serial {sr}, production{prod} {
                std::cout << "Constructor\n";
            };

        Tag(const Tag& tag) : serial{tag.serial}, \
            production{tag.production} {
                std::cout << "Copy constructor\n";
            };

        Tag& operator=(const Tag& tag) {
            std::cout << "Copy operator\n";
            if(this == &tag) {
                return *this;
            }
            serial = tag.serial;
            production = tag.production;
        }


        Tag(Tag&& tag) : serial {tag.serial}, \
            production{tag.production} {
                std::cout << "Move constructor\n";
                tag.serial = std::string {};
                tag.production = std::string {};
            };

        Tag& operator=(Tag&& tag) {
            std::cout << "Move operator\n";
            std::swap(serial, tag.serial);
            std::swap(production, tag.production);
            return *this;
        };
    
        const std::string& getSerial() const {
            return serial;
        }

        const std::string& getProduction() const {
            return production;
        }

    private :
        std::string serial;
        std::string production;
};

Tag nextModel() {
    std::cout << "in nextModel()::";
    Tag advancedModel {"RUVX7", "Bavaria"};
    return advancedModel;
}

std::ostream& operator<<(std::ostream& os, const Tag& tag) {
    os << "-----------------------------------------\n" \
       << "Serial : " << tag.getSerial() << "\n" \
       << "Production : " << tag.getProduction() << "\n" \
       << "-----------------------------------------\n";
    return os;
}

int main() {
    Tag model {};
    std::cout << model;
    model = nextModel();
    std::cout << model;
    Tag newGen {std::move(model)};
    std::cout << newGen;
    std::cout << model;
    model = std::move(nextModel());
    return 0;
}
