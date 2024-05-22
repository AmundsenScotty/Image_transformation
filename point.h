#ifndef POINT_H
#define POINT_H

    #include <iostream>

    /// Point structure
    /// Represents a point on the image
    struct Point
    {
        int x;
        int y;

        /// Constructor
        // @param px - x coordinate
        // @param py - y coordinate
        explicit Point(int px = 0, int py = 0) : x(px), y(py) {}

        /// Dictance between two points
        // @param a - first point
        // @param b - second point
        // @return distance as unsigned integer
        static unsigned distance(Point const& a, Point const& b);
    };


    /// Input operator
    // @param is - input stream
    // @param p - point
    // @return same input stream
    std::istream& operator>>(std::istream& is, Point& p);

#endif