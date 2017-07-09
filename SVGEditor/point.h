#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>

struct Point
{
    double x;
    double y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

inline std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << p.x << " " << p.y;
    return os;
}
#endif // POINT_H_INCLUDED
