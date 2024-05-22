#ifndef VECTOR_H
#define VECTOR_H

	#include "point.h"

	struct Vector
	{
		double x;
		double y;

		Vector(double px, double py) : x(px), y(py) {}
		Vector(Point const& a, Point const& b);

		double len() const;

		static Vector distance(Vector const& a, Vector const& b);
	};

#endif