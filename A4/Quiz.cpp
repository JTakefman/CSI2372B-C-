#include <vector>
#include <iostream>

struct Point {
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
};

int main() {
    std::vector<Point> points = {{1,2}, {3,4}, {5,6}};
    for(auto it = points.begin(); it != points.end(); ++it) {
        Point p = *it;
        std::cout << "Point (" << p.x << ", " << p.y<< ")" << std::endl;
    }
    return 0;
}