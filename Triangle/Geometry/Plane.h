#pragma once

#include "Vector.h"
#include <cmath>
#include <ostream>
#include <istream>

namespace geom{
class Line;

class Plane
    {
    private:
        Vector normal_;
        double D_;
    public:
        Plane(const Vector& p1, const Vector& p2, const Vector& p3);
        Plane() = default;
        double A() const {return normal_.x;}
        double B() const {return normal_.y;}
        double C() const {return normal_.z;}
        double D() const {return D_;}
        Vector normal() const {return normal_;}
        bool Is_valid() const;
    };
inline std::ostream& operator << (std::ostream& stream, const Plane& plane) {return stream << "A = " << plane.A() << " B = " << plane.B() << " C = " << plane.C() << " D = " << plane.D() << std::endl;}

bool Is_parallel(const Plane& plane1, const Plane& plane2);
bool Is_equal(const Plane& first, const Plane& second);
bool Is_point_on_plane(const Plane& plane, const Vector& point);
Plane Search_common_plane(const Line& line1, const Line& line2);
}
