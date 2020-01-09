//
// Created by Mor on 09/01/2020.
//

#include <functional>

#include "../../UniqueArray.h"

class Point {
private:
    int x;
    int y;
public:
    Point() : x(0), y(0) {
    }

    Point(int x, int y) : x(x), y(y) {}
    bool operator==(const Point& point) const {
        return (point.x == this->x) && (point.y == this->y);
    }

    int getX() const {
        return this->x;
    }
};

void testFilter() {
    typedef UniqueArray<Point, std::equal_to<Point>> PointUA;
    int size = 3;
    Point point = Point();
    Point point1 = Point(1,1);
    Point point100 = Point(100, 100);
    class LessThan5 : public PointUA::Filter {
    public:
        virtual bool operator() (Point const & element) const override {
            return element.getX() < 5;
        }
    };

    PointUA pUA(size);
    pUA.insert(point);
    pUA.insert(point1);
    pUA.insert(point100);

    PointUA filtered = pUA.filter(LessThan5());
    const Point *p100 = filtered[point100];

}

int main() {
    testFilter();
    return 0;
}