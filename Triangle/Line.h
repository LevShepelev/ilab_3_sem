#pragma once

#include "Vector.h"
#include "Plane.h"

class Line
    {
    private: 
        Vector point_, direction_;
    public:
        Line(){}
        Line(Vector p1, Vector p2);
        Line(Plane first, Plane second);
        Vector point() const {return point_;}
        Vector direction() const {return direction_;}
    };
std::ostream& operator << (std::ostream& stream, const Line& line) {return stream << "point = " << line.point() << "direction = " << line.direction() << std::endl;}


Line::Line(Plane first, Plane second) // Line constructor, return crossing line of two planes
    {
    direction_ = Vect_mul(first.N(), second.N());
    if (!(direction_ == Vector(0, 0, 0)))
        {
        double a = ((-second.D()) * first.N() * second.N() + first.D() * second.N() * second.N()) / ((first.N() * second.N()) * (first.N() * second.N()) - (first.N() * first.N()) * (second.N() * second.N()));
        double b = ((-first.D()) * first.N() * second.N() + second.D() * first.N() * first.N()) / ((first.N() * second.N()) * (first.N() * second.N()) - (first.N() * first.N()) * (second.N() * second.N())); // Geometric Tools for Computer Graphics page 531
        point_ = first.N() * a + second.N()  * b;
        }
    else if ((first.A() != 0 && Is_zero(-first.D() / first.A() * second.A() + second.D())) || (first.B() != 0 && Is_zero(-first.D() / first.B() * second.B() + second.D())) || (first.C() != 0 && Is_zero(-first.D() / first.C() * second.C() + second.D())))
        point_ = Vector (nan(""), nan(""), nan("")); //Planes are parallel, we cant create crossing line"
    else
        point_ = Vector(nan(""), nan(""), nan("")); //Planes are parallel, we cant create crossing line"
    }

Line::Line(Vector p1, Vector p2)
    {
    direction_ = p2 - p1;
    point_ = p1;
    }