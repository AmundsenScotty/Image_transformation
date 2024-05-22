#include <cmath>
#include <istream>

#include "point.h"
#include "vector.h"

unsigned Point::distance(Point const &a, Point const &b)
{
    return Vector(a, b).len();
}

std::istream& operator>>(std::istream& is, Point& p)
{
    is >> p.x >> p.y;
    return is;
}