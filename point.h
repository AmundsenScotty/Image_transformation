#ifndef POINT_H
#define POINT_H

    #include <iostream>

    struct Point
    {
        int x;
        int y;

        explicit Point(int px = 0, int py = 0) : x(px), y(py) {}

        static unsigned distance(Point const& a, Point const& b);
    };

    std::istream& operator>>(std::istream& is, Point& p);

#endif