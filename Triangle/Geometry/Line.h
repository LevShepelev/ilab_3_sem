#pragma once

#include "Vector.h"
#include "Plane.h"
#include <cmath>
#include <ostream>

namespace geom {

class Line
    {
    private: 
        Vector point_, direction_;
    public:
        Line() = default;
        Line(const Vector& p1, const Vector& p2);
        Line(const Plane& first, const Plane& second);
        Vector point() const {return point_;}
        Vector direction() const {return direction_;}
        bool Is_valid() const;
    };
inline std::ostream& operator << (std::ostream& stream, const Line& line) {return stream << "point = " << line.point() << "direction = " << line.direction() << std::endl;}

bool Is_point_on_line(Line line, Vector point);
bool Is_lines_in_one_plane(Line line_1, Line line_2);
double Coefficent_for_finding_common_point_of_two_planes(const Plane& first, const Plane& second);
}