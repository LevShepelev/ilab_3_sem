#include "Line.h"

namespace geom{

Line::Line(const Plane& first, const Plane& second) // Line constructor, return crossing line of two planes
    {
    direction_ = Vect_mul(first.normal(), second.normal());
    if (!(direction_ == Vector(0, 0, 0)))
        {
        double a = Coefficent_for_finding_common_point_of_two_planes(first, second);
        double b = Coefficent_for_finding_common_point_of_two_planes(second, first);
        point_ = first.normal() * a + second.normal() * b;
        }
    else if (Is_equal(first, second))
        point_ = Vector (nan(""), nan(""), nan("")); //Planes are equal, we cant create crossing line"
    else
        point_ = Vector (nan(""), nan(""), nan("")); //Planes are parallel, we cant create crossing line"
    }


// Geometric Tools for Computer Graphics page 531
double Coefficent_for_finding_common_point_of_two_planes(const Plane& first, const Plane& second)
    {
    return ((-second.D()) * first.normal() * second.normal() + first.D() * second.normal() * second.normal()) /             
           ((first.normal() * second.normal()) * (first.normal() * second.normal()) - (first.normal() * first.normal()) * (second.normal() * second.normal()));
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
}