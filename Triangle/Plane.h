#pragma once

#include "Vector.h"


class Plane
    {
    private:
        Vector N_;
        double A_, B_, C_, D_;
    public:
        Plane(Vector p1, Vector p2, Vector p3);
        Plane() : A_(0), B_(0), C_(0), D_(0) {}
        double A() const {return A_;}
        double B() const {return B_;}
        double C() const {return C_;}
        double D() const {return D_;}
        Vector N() const {return N_;}
    };
std::ostream& operator << (std::ostream& stream, const Plane& plane) {return stream << "A = " << plane.A() << "B = " << plane.B() << "C = " << plane.C() << std::endl;}

Plane::Plane(Vector p1, Vector p2, Vector p3)
    {
    A_ = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
    B_ = -(p2.x - p1.x) * (p3.z - p1.z) + (p2.z - p1.z) * (p3.x - p1.x);
    C_ = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    D_ = -p1.x * A_ - p1.y * B_ - p1.z * C_;
    N_ = Vector(A_, B_, C_);
    }

