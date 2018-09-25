/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   26 August, 2018 
 *  Summary :   Use constexpr object and constexpr function.
 */

class Point {
public :
    constexpr Point(double x_value = 0, double y_value = 0) : x{x_value}, y{y_value} {}
    
    constexpr double x_value() const { return x; }
    constexpr double y_value() const { return y; }
private :
    double x;
    double y;
};

class Phasor {
    constexpr Phase(double amplitude = 0, double phase = 0) : a{amplitude}, p{phase} {}

    constexpr double amplitude() const { return a; }
    constexpr double phase() const { return p; }
private :
    double amplitude;
    double phase;
}

constexpr
Point mid_point(const Point& p, const Point& q) {
    return {(p.x_value() + q.x_value())/2, (p.y_value() + q.y_value())/2};
}

/*
constexpr
double amplitude(const Point& p) {
    // 불행하게도, STL에서 std::sqrt와 std::pow가 constexpr로 정의되어 있지 않다.
    // 따라서, 직접 sqrt와 pow를 작성해야 한다.
}

constexpr
double phase(const Point& p) {
    // 마찬가지로, std::atan 또한 constexpr로 명세되어 있지 않다!
}

constexpr
Point point_to_phasor(const Point& p) {
    return { };
}
*/

void print_point(const Point& p) {
    cout << "Point = (" << p.x_value() << " , " << p.y_value() << ")" << endl;
}

void foo() {
    Point a {1.0, 2.0};
    Point b {-1.0, -2.0};
    Point orig = mid_point(a, b);
}

int main() {
    foo();
    return 0;
}
