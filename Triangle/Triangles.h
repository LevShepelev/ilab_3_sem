#pragma once

#include <istream>
#include <iostream>
#include <ostream>
#include <cmath>
#include <vector>
#include "Line.h"
#include "Plane.h"
#include "Vector.h"

class Vector;
class Line;
class Plane;
class Triangle;
bool Triangle_crossing(Triangle tr1, Triangle tr2);
std::vector<Vector> Triangle_and_line_crossing(Line line, Triangle triangle);
Vector Intersection_point_on_plane(const Line& line1, const Line& line2, Plane plane);

class Triangle
    {
    private:
        Vector p1_, p2_, p3_;
        Plane plane_;
        Line line1_, line2_, line3_;
    public:
        Triangle(){}
        Triangle(Vector p1, Vector p2, Vector p3);
        Vector p1()   const {return p1_;}
        Vector p2()   const {return p2_;}
        Vector p3()   const {return p3_;}
        Plane plane() const {return plane_;}
        Line line1()  const {return line1_;}
        Line line2()  const {return line2_;}
        Line line3()  const {return line3_;}
    };

Triangle::Triangle(Vector p1, Vector p2, Vector p3) : p1_(p1), p2_(p2), p3_(p3), plane_(p1, p2, p3)
    {
    plane_ = Plane(p1_, p2_, p3_);
    line1_ = Line(p1_, p2_);
    line2_ = Line(p2_, p3_);
    line3_ = Line(p3_, p1_);
    }


Vector Intersection_point_on_plane(const Line& line1, const Line& line2, Plane plane) // The function searhces crossing point of two lines that lay in one plane
    {
    if (Vect_mul(line1.direction(), line2.direction()) == Vector(0, 0, 0))
        return Vector(nan(""), nan(""), nan("")); //Lines are parallel, we cannot choose one point
    else 
        {
        Vector shift_point; //If plane goes through (0, 0, 0) we have to move starting point, shift_point is our shifting
        if (Is_zero(plane.D()))
            shift_point = plane.N();
        else shift_point = Vector(0, 0, 0);
        double s = Comb_mul(line2.point() - shift_point, line1.point() - shift_point, line1.direction()) / Comb_mul(line2.point() - shift_point, line2.direction(), line1.direction());
        return Vector(line2.point().x + s * line2.direction().x, line2.point().y + s * line2.direction().y, line2.point().z + s * line2.direction().z);
        }
    }

bool Triangle_crossing(Triangle tr1, Triangle tr2) // The function get segments and research theirs mutual arrangement
    {
    Line crossing_line(tr1.plane(), tr2.plane());
    std::vector<Vector> segment_1 = Triangle_and_line_crossing(crossing_line, tr1), 
                        segment_2 = Triangle_and_line_crossing(crossing_line, tr2);
    if (segment_1.size() == 2 && segment_2.size() == 2 &&
        (segment_1[0].Is_point_between_other_points(segment_2[0], segment_2[1]) || segment_1[1].Is_point_between_other_points(segment_2[0], segment_2[1])))
        return true;

    else if (segment_1.size() == 1 && segment_2.size() == 2 && segment_1[0].Is_point_between_other_points(segment_2[0], segment_2[1]))
        return true;

    else if (segment_1.size() == 2 && segment_2.size() == 1 && segment_2[0].Is_point_between_other_points(segment_1[0], segment_1[1]))
        return true;

    else if (segment_1.size() == 1 && segment_2.size() == 1 && (segment_1[0] == segment_2[0]))
        return true;

    else return false;
    }


std::vector<Vector> Triangle_and_line_crossing(Line line, Triangle triangle) //The function searchers intersection of crossing_line and triangle and return segments
    {
    std::vector<Vector> segment;
    Vector p1 = Intersection_point_on_plane(line, triangle.line1(), triangle.plane());
    Vector p2 = Intersection_point_on_plane(line, triangle.line2(), triangle.plane());
    Vector p3 = Intersection_point_on_plane(line, triangle.line3(), triangle.plane());
    if (p1.Is_point_between_other_points(triangle.p1(), triangle.p2()) || p1.Is_point_between_other_points(triangle.p2(), triangle.p3()) || p1.Is_point_between_other_points(triangle.p3(), triangle.p1()))
        segment.push_back(p1);

    if (p2.Is_point_between_other_points(triangle.p1(), triangle.p2()) || p2.Is_point_between_other_points(triangle.p2(), triangle.p3()) || p2.Is_point_between_other_points(triangle.p3(), triangle.p1()))
        segment.push_back(p2);


    if ((p3.Is_point_between_other_points(triangle.p1(), triangle.p2()) || p3.Is_point_between_other_points(triangle.p2(), triangle.p3()) || p3.Is_point_between_other_points(triangle.p3(), triangle.p1())) && segment.size() < 2)
        segment.push_back(p3);

    return segment;
    }

