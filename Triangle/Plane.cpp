#include "Line.h"
#include "Plane.h"

namespace geom{
Plane::Plane(const Vector& p1, const Vector& p2, const Vector& p3)
    {
    double A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y),
           B = -(p2.x - p1.x) * (p3.z - p1.z) + (p2.z - p1.z) * (p3.x - p1.x),
           C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    if ((A != 0 || B != 0 || C != 0) && p1.Is_valid() && p2.Is_valid() && p3.Is_valid())
        {
        D_ = -p1.x * A - p1.y * B - p1.z * C;
        normal_ = Vector(A, B, C);
        }
    else 
        {
        D_ = nan("");
        normal_ = Vector();
        }
    }

bool Plane::Is_valid() const
    {
    if (normal_.Is_valid() && std::isfinite(D_))
        return true;
    return false;
    }


bool Is_parallel(const Plane& plane1, const Plane& plane2)
    {
    if (Vect_mul(plane1.normal(), plane2.normal()) == Vector(0, 0, 0)) 
        return true;
    return false;
    }


bool Is_equal(const Plane& first, const Plane& second)
    {
    
    if (Vect_mul(first.normal(), second.normal()) == Vector(0, 0, 0) && first.Is_valid() && second.Is_valid()) 
        if ((first.A() != 0 && Is_zero(-first.D() / first.A() * second.A() + second.D())) || 
            (first.B() != 0 && Is_zero(-first.D() / first.B() * second.B() + second.D())) ||
            (first.C() != 0 && Is_zero(-first.D() / first.C() * second.C() + second.D())))
            return true;
    return false;
    }


bool Is_point_on_plane(const Plane& plane, const Vector& point)
    {
    if (Is_zero(point * plane.normal() + plane.D()))
        return true;
    else return false;
    }

/// \brief The function consturct plane for two lines lay in that plane
Plane Search_common_plane(const Line& line1, const Line& line2)
    {
    if (!(line1.point() == line2.point()))
        if (!(line1.point() == line2.point() + line2.direction()))
            return Plane(line1.point(), line2.point(), line2.point() + line2.direction()); //Points can be equal, so we check are they equal and make cases
        else return Plane(line1.point(), line2.point(), line2.point() + 2 * line2.direction());
    else return Plane(line1.point(), line2.point() + line2.direction(), line2.point() + 2 * line2.direction());
    }  
}