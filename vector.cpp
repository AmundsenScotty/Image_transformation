#include <cmath>

#include "vector.h"

/// Constructs a vector from two points.
/// @param a The starting point of the vector.
/// @param b The ending point of the vector.
Vector::Vector(Point const& a, Point const& b)
{
    x = b.x - a.x;
    y = b.y - a.y;
}

/// Calculates the length of the vector.
/// @return The length of the vector.
double Vector::len() const
{
    return sqrt(x * x + y * y);
}

/// Calculates the distance between two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The distance between the two vectors.
Vector Vector::distance(Vector const& a, Vector const& b)
{
    return Vector(b.x - a.x, b.y - a.y);
}
