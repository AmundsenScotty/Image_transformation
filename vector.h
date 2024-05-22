#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"
	

/// Vector class
// Represents a vector on the image
struct Vector
{
	double x;
	double y;

	/// Constructor: creates a vector from the origo to coordinates
	// @param px - x coordinate
	// @param py - y coordinate
	Vector(double px, double py) : x(px), y(py) {}

	/// Constructor: creates a vector from point a to point b
	// @param a - start point
	// @param b - end point
	Vector(Point const& a, Point const& b);


	/// Returns the length of the vector
	// @return length of the vector
	double len() const;

	/// Returns the distance between two vectors
	// @param a - first vector
	// @param b - second vector
	// @return distance between the two vectors in x, y vecotr coordinates
	static Vector distance(Vector const& a, Vector const& b);
};

#endif