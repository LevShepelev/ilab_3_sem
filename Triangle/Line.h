#pragma once

#include "Vector.h"
#include "Plane.h"
#include <cmath>

class Line
    {
    private: 
        Vector point_, direction_;
    public:
        Line() : point_(Vector()), direction_(Vector()) {}
        Line(const Vector& p1, const Vector& p2);
        Line(const Plane& first, const Plane& second);
        Vector point() const {return point_;}
        Vector direction() const {return direction_;}
        bool Is_valid() const;
    };
std::ostream& operator << (std::ostream& stream, const Line& line) {return stream << "point = " << line.point() << "direction = " << line.direction() << std::endl;}

Line::Line(const Plane& first, const Plane& second) // Line constructor, return crossing line of two planes
    {
    direction_ = Vect_mul(first.normal(), second.normal());
    if (!(direction_ == Vector(0, 0, 0)))
        {
        double a = ((-second.D()) * first.normal() * second.normal() + first.D() * second.normal() * second.normal()) / ((first.normal() * second.normal()) * (first.normal() * second.normal()) - (first.normal() * first.normal()) * (second.normal() * second.normal()));
        double b = ((-first.D()) * first.normal() * second.normal() + second.D() * first.normal() * first.normal()) / ((first.normal() * second.normal()) * (first.normal() * second.normal()) - (first.normal() * first.normal()) * (second.normal() * second.normal())); // Geometric Tools for Computer Graphics page 531
        point_ = first.normal() * a + second.normal() * b;
        }
    else if (Is_equal(first, second))
        point_ = Vector (nan(""), nan(""), nan("")); //Planes are equal, we cant create crossing line"
    else
        point_ = Vector (nan(""), nan(""), nan("")); //Planes are parallel, we cant create crossing line"
    }

Line::Line(const Vector& p1, const Vector& p2)
    {
    direction_ = p2 - p1;
    point_ = p1;
    }

bool Line::Is_valid() const
    {
    if (direction_ == Vector(0, 0, 0))
        return false;
    return true;
    }

bool Is_lines_in_one_plane(Line line_1, Line line_2)
    {
    return Is_zero(Comb_mul(line_1.direction(), line_2.direction(), line_1.point() - line_2.point()));
    }

bool Is_point_on_line(Line line, Vector point)
    {
    if (line.Is_valid())
        if (point - point * line.direction() / sqr_length(line.direction()) * line.direction() == line.point() - line.point() * line.direction() / sqr_length(line.direction()) * line.direction())
            return true;
    return false;
    }