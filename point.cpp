#include <cmath>
#include <istream>

#include "point.h"
#include "vector.h"

/// Calculates the distance between two points using a vector.
/// @param a The first point.
/// @param b The second point.
/// @return The distance between points a and b.
unsigned Point::distance(Point const& a, Point const& b)
{
    return Vector(a, b).len();      // creates a vector from a to b and returns its length
}

/// Overloads the extraction operator to read a point from an input stream.
/// @param is The input stream.
/// @param p The point to read.
/// @return The input stream.
std::istream& operator>>(std::istream& is, Point& p)
{
    is >> p.x >> p.y;
    return is;
}
