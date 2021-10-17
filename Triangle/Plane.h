#pragma once

#include "Vector.h"

class Plane
    {
    private:
        Vector N_;
        double D_;
    public:
        Plane(const Vector& p1, const Vector& p2, const Vector& p3);
        Plane() : D_(nan("")), N_(Vector()) {}
        double A() const {return N_.x;}
        double B() const {return N_.y;}
        double C() const {return N_.z;}
        double D() const {return D_;}
        Vector N() const {return N_;}
        bool Is_valid() const;
    };
std::ostream& operator << (std::ostream& stream, const Plane& plane) {return stream << "A = " << plane.A() << "B = " << plane.B() << "C = " << plane.C() << std::endl;}

Plane::Plane(const Vector& p1, const Vector& p2, const Vector& p3)
    {
    double A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y),
           B = -(p2.x - p1.x) * (p3.z - p1.z) + (p2.z - p1.z) * (p3.x - p1.x),
           C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    D_ = -p1.x * A - p1.y * B - p1.z * C;
    N_ = Vector(A, B, C);
    }

bool Is_parallel(const Plane& plane1, const Plane& plane2)
    {
    if (Vect_mul(plane1.N(), plane2.N()) == Vector(0, 0, 0)) 
        return true;
    return false;
    }

bool Is_equal(const Plane& first, const Plane& second)
    {
    
    if (Vect_mul(first.N(), second.N()) == Vector(0, 0, 0) && first.Is_valid() && second.Is_valid()) 
        if ((first.A() != 0 && Is_zero(-first.D() / first.A() * second.A() + second.D())) || (first.B() != 0 && Is_zero(-first.D() / first.B() * second.B() + second.D())) || (first.C() != 0 && Is_zero(-first.D() / first.C() * second.C() + second.D())))
            return true;
    return false;
    }

bool Plane::Is_valid() const
    {
    if (N_.Is_valid() && std::isfinite(D_))
        return true;
    return false;
    }

