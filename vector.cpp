#include <cmath>

#include "vector.h"

Vector::Vector(Point const& a, Point const& b)
{
	x = b.x - a.x;
	y = b.y - a.y;
}

double Vector::len() const
{
	return sqrt(x * x + y * y);
}

Vector Vector::distance(Vector const& a, Vector const& b)
{
	return Vector(b.x - a.x, b.y - a.y);
}