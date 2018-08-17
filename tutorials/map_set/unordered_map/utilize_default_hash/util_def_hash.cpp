/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   August 17, 2018
 *
 */

 /*
  * Summary :   Create a hash function by utilizing standard(default) hash template and exclusive OR operations.
  */

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

struct Name
{
    string first;
    string last;
};

void test_hf()
{
    Name me {"Gu-hwan", "Bae"};
    Name you {"Linus", "Torvalds"};

    auto hf = [](const Name& n) {
        cout << n.first << " " << n.last << endl;
        size_t h1 = hash<string>{}(n.first);
        size_t h2 = hash<string>{}(n.last);
        cout << "h1 = " << h1 << ", h2 = " << h2 << endl;
        cout << "h1 ^ h2 = " << (h1^h2) << endl;
    };

    hf(me);
    hf(you);
}

void test_hashset()
{
    Name kf {"kakao", "ryan"};
    Name kf_copy {"kakao", "ryan"};
    Name lf {"line", "brown"};
    Name simpsons {"simpsons", "bart"};

    auto hf = [](const Name& n) { return hash<string>{}(n.first)^hash<string>{}(n.last); };
    auto eq = [](const Name& p, const Name& q) { return (p.first==q.first) && (p.last==q.last); };
    unordered_set<Name, decltype(hf), decltype(eq)> hs {20, hf, eq};

    hs.insert(kf);
    hs.insert(lf);

    auto p = hs.find(kf_copy);
    if(p != hs.end())
    {
        cout << kf_copy.last << " in here." << endl;
    }
    p = hs.find(simpsons);
    if(p == hs.end())
    {
        cout << simpsons.last << " no here." << endl;
    }
}

int main() {
    cout << "Test a hash function." << endl;
    test_hf();
    cout << "Test a hash set." << endl;
    test_hashset();

    return 0;
}
