#pragma once
 
#include <algorithm>
#include <istream>
#include <iostream>
#include <ostream>
#include <cmath>
#include <vector>
#include "Triangles.h"

namespace geom{

bool Triangle_crossing(const Triangle& tr1, const Triangle& tr2);
std::vector<Vector> Triangle_and_line_crossing(Line line, Triangle triangle);
Vector Intersection_point_on_plane(const Line& line1, const Line& line2, Plane plane);
bool Triangles_crossing_in_one_plane(Triangle tr1, Triangle tr2);
bool Is_point_inside_triangle(const Vector& point, const Triangle& tr1);
bool Triagnle_crossing_invalide_cases(const Triangle& tr1, const Triangle& tr2);
bool Triangle_and_line_interesection_in_3D(const Line& line, const Triangle& tr);
bool Will_we_compare(std::vector<Triangle> triangles, int i, int j);
bool Invalid_case_two_line(const Triangle& tr1, const Triangle& tr2);
bool Invalid_case_Trinagle_line(const Triangle& tr1, const Triangle tr2);
bool Invalid_case_line_point(const Triangle& tr1, const Triangle tr2);
};