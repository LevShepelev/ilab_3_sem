#pragma once

#include <algorithm>
#include <istream>
#include <iostream>
#include <ostream>
#include <cmath>
#include <vector>
#include "Line.h"
#include "Plane.h"
#include "Vector.h"

class Line;
class Plane;
class Triangle;
bool Triangle_crossing(const Triangle& tr1, const Triangle& tr2);
std::vector<Vector> Triangle_and_line_crossing(Line line, Triangle triangle);
Vector Intersection_point_on_plane(const Line& line1, const Line& line2, Plane plane);
bool Triangles_crossing_in_one_plane(Triangle tr1, Triangle tr2);
bool Is_point_inside_triangle(const Vector& point, const Triangle& tr1);
void Calculating_the_task();
bool Triagnle_crossing_invalide_cases(const Triangle& tr1, const Triangle& tr2);
bool Triangle_and_line_interesection_in_3D(const Line& line, const Triangle& tr);
Plane Search_common_plane(const Line& line1, const Line& line2);
bool comparator_x(Triangle* tr1, Triangle* tr2);
bool Will_we_compare(Triangle* triangles[], int i);

const char poison = 255;

class Triangle
    {
    private:
        char min_coord_[3];
        char max_coord_[3];
        Vector p_[3];
        Plane plane_;
        Line line_[3];
        unsigned int number_ = 0;

    public:
        Triangle(){}
        Triangle(Vector p1, Vector p2, Vector p3, int n);
        bool Is_valid() const {return plane_.Is_valid();}

    public: //getters
        Plane plane() const {return plane_;}
        Vector p(int i)  const   {if (1 <= i && i <= 3) return p_[i - 1]; else return Vector();}
        Line line(int i) const   {if (1 <= i && i <= 3) return line_[i - 1]; else return Line();}
        double min_coord(int i) const {if (0 <= i && i <= 2) return p_[min_coord_[i]][i]; else return poison;}
        double max_coord(int i) const {if (0 <= i && i <= 2) return p_[max_coord_[i]][i]; else return poison;}
        unsigned int number() const {return number_;}
    };

Triangle::Triangle(Vector p1, Vector p2, Vector p3, int n) : p_({p1, p2, p3}), plane_(p1, p2, p3), number_(n)
    {
    for (int i = 0; i < 3; i++)// i is coordinate 0 = x, 1 = y, 2 = z;
        {
        if (p_[0][i] > p_[1][i])
            { 
            if (p_[0][i] > p_[2][i]) max_coord_[i] = 0;
            else max_coord_[i] = 2;
            if (p_[1][i] < p_[2][i]) min_coord_[i] = 1;
            else min_coord_[i] = 2;
            }
        else 
            {
            if (p_[1][i] > p_[2][i]) max_coord_[i] = 1;
            else max_coord_[i] = 2;
            if (p_[0][i] < p_[2][i]) min_coord_[i] = 0;
            else min_coord_[i] = 2;
            }
        }
    line_[0] = Line(p1, p2);
    line_[1] = Line(p2, p3);
    line_[2] = Line(p3, p1);
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

bool Triangle_crossing(const Triangle& tr1, const Triangle& tr2) // The function get segments and research theirs mutual arrangement
    {
    std::cout << tr1.plane() << tr2.plane() << std::endl;
    if (!tr1.Is_valid() || !tr2.Is_valid())
        return Triagnle_crossing_invalide_cases(tr1, tr2);
        
    if (Is_equal(tr1.plane(), tr2.plane()))
        return Triangles_crossing_in_one_plane(tr1, tr2);
        
    else if (Is_parallel(tr1.plane(), tr2.plane()))
        return false;

    else 
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
    }

bool Triangles_crossing_in_one_plane(Triangle tr1, Triangle tr2) //The function finds out if triangles intersect
    {
    std::vector<Vector> segments[3];
    segments[0] = Triangle_and_line_crossing(tr1.line(1), tr2);
    segments[1] = Triangle_and_line_crossing(tr1.line(2), tr2);
    segments[2] = Triangle_and_line_crossing(tr1.line(3), tr2);

    if ((segments[0].size() > 0 || segments[1].size() > 0 || segments[2].size() > 0) || Is_point_inside_triangle(tr1.p(1), tr2) || Is_point_inside_triangle(tr2.p(1), tr1)) //second or, third or cases are about full triangle lay in other 
        return true;
    return false;
    }


std::vector<Vector> Triangle_and_line_crossing(Line line, Triangle triangle) //The function searchers intersection of crossing_line and triangle(they are in one plane) and return segments
    {
    std::vector<Vector> segment;
    Vector p1 = Intersection_point_on_plane(line, triangle.line(1), triangle.plane());
    Vector p2 = Intersection_point_on_plane(line, triangle.line(2), triangle.plane());
    Vector p3 = Intersection_point_on_plane(line, triangle.line(3), triangle.plane());

    if (p1.Is_point_between_other_points(triangle.p(1), triangle.p(2)) || p1.Is_point_between_other_points(triangle.p(2), triangle.p(3)) || p1.Is_point_between_other_points(triangle.p(3), triangle.p(1)))
        segment.push_back(p1);

    if (p2.Is_point_between_other_points(triangle.p(1), triangle.p(2)) || p2.Is_point_between_other_points(triangle.p(2), triangle.p(3)) || p2.Is_point_between_other_points(triangle.p(3), triangle.p(1)))
        segment.push_back(p2);

    if (segment.size() < 2 && (p3.Is_point_between_other_points(triangle.p(1), triangle.p(2)) || p3.Is_point_between_other_points(triangle.p(2), triangle.p(3)) || p3.Is_point_between_other_points(triangle.p(3), triangle.p(1))) )
        segment.push_back(p3);

    return segment;
    }

void Calculating_the_task()
    {
    unsigned int N = 0;
    std::cin >> N;
    Triangle* triangles[N];
    bool crossing_triangles[N];
    for (int i = 0; i < N; i++)
        {
        Vector p1, p2, p3;
        std::cin >> p1 >> p2 >> p3;
        triangles[i] = new Triangle(p1, p2, p3, i);
        crossing_triangles[i] = false;
        }
    for (int j = 0; j < N; j++)
        std::cout << triangles[j] -> plane() << std::endl;
    std::sort(triangles, triangles + N, comparator_x);
    for (int i = 1; i < N; i++)
        {
        for (int j = 0; j < 3; j++)
            printf("min(%d) = %lf, max(%d) = %lf\n", i, triangles[i] -> min_coord(j), i - 1, triangles[i - 1] -> max_coord(j));
        if (Triangle_crossing(*triangles[i], *triangles[i - 1]) && Will_we_compare(triangles, i))
            {
            crossing_triangles[triangles[i - 1] -> number()] = true;
            crossing_triangles[triangles[i] -> number()] = true;
            }
            
        }
    for (int i = 0; i < N; i++)
        {
        if (crossing_triangles[i] == true)
            std::cout << i << std::endl;
        delete triangles[i];
        }
    
    }

bool Will_we_compare(Triangle* triangles[], int i)
    {
    if  (((triangles[i] -> min_coord(0) <= triangles[i - 1] -> max_coord(0))
        &&(triangles[i] -> min_coord(1) <= triangles[i - 1] -> max_coord(1))
        &&(triangles[i] -> min_coord(2) <= triangles[i - 1] -> max_coord(2)))
        || !(triangles[i] -> Is_valid()) || !(triangles[i] -> Is_valid()))
        return true;
    else return false;
    }

bool comparator_x(Triangle* tr1, Triangle* tr2)
    { 
    if (tr1 -> min_coord(0) - tr2 -> min_coord(0) > epsilon) return true;
    else return false;
    }

bool Is_point_inside_triangle(const Vector& point, const Triangle& tr1) //The function finds out is point inside the triangle, (triangle and point must lay in one plane)
    {
    if (Is_zero(point * tr1.plane().N() + tr1.plane().D()))
        {
        double  cb1 = Comb_mul(tr1.plane().N(), tr1.p(1) - point, tr1.p(2) - point),
                cb2 = Comb_mul(tr1.plane().N(), tr1.p(2) - point, tr1.p(3) - point),
                cb3 = Comb_mul(tr1.plane().N(), tr1.p(3) - point, tr1.p(1) - point);
        if ((cb1 >= 0 && cb2 >= 0 && cb3 >= 0) || (cb1 <= 0 && cb2 <= 0 && cb3 <= 0))
            return true;
        else return false; 
        }
    else return false;
    }

bool Triagnle_crossing_invalide_cases(const Triangle& tr1, const Triangle& tr2)
    {
    printf("invalid\n");
    for (int i = 1; i <= 3; i++)   //triangle and line
        if (!tr1.Is_valid() && tr2.Is_valid() && tr1.line(i).Is_valid())
            return Triangle_and_line_interesection_in_3D(tr1.line(i), tr2);

    for (int j = 1; j <= 3; j++)   //triangle and line
        if (tr1.Is_valid() && !tr2.Is_valid() && tr2.line(j).Is_valid())
            return Triangle_and_line_interesection_in_3D(tr2.line(j), tr1);
            
    for (int i = 1; i <= 3; i++)   //two lines
        if (tr1.line(i).Is_valid())
            for (int j = 1; j <= 3; j++)
                if (tr2.line(2).Is_valid())
                    if (Is_lines_in_one_plane(tr1.line(i), tr2.line(j)))
                        {
                        Vector p = Intersection_point_on_plane(tr1.line(i), tr2.line(j), Search_common_plane(tr1.line(i), tr2.line(j)));
                        if (p.Is_point_between_other_points(tr1.p(i), tr1.p(i % 3 + 1)) && p.Is_point_between_other_points(tr2.p(j), tr2.p(j % 3 + 1))) // j % 3 + 1 is next point to j
                            return true;
                        }

    if (tr1.Is_valid() && !tr2.Is_valid() && Is_point_on_plane(tr1.plane(), tr2.p(1)) && Is_point_inside_triangle(tr2.p(1), tr1) || //one triangle and point
        tr2.Is_valid() && !tr1.Is_valid() && Is_point_on_plane(tr2.plane(), tr1.p(1)) && Is_point_inside_triangle(tr1.p(1), tr2))
        return true;

    if () //to do line and point
        {
        }
    if (!tr1.Is_valid() && !tr2.Is_valid() && (tr1.p(1) == tr2.p(1))) //triangles are points
        return true;

    return false;
                    
    }

bool Triangle_and_line_interesection_in_3D(const Line& line, const Triangle& tr)
    {
    if (!line.Is_valid())
        {
        printf("invalid line\n");
        return false;
        }
    double t = (-tr.plane().D() - line.point().x * tr.plane().N().x - line.point().y * tr.plane().N().y - line.point().z * tr.plane().N().z) / (line.direction().x + line.direction().y + line.direction().z);
    return Is_point_inside_triangle(Vector(line.point().x + t * line.direction().x, line.point().y + t * line.direction().y, line.point().z + t * line.direction().z), tr);
    }

Plane Search_common_plane(const Line& line1, const Line& line2) //Plane consturctor for two lines lay in that plane
    {
    if (!(line1.point() == line2.point()))
        if (!(line1.point() == line2.point() + line2.direction()))
            return Plane(line1.point(), line2.point(), line2.point() + line2.direction()); //Points can be equal, so we check are they equal and make cases
        else return Plane(line1.point(), line2.point(), line2.point() + 2 * line2.direction());
    else return Plane(line1.point(), line2.point() + line2.direction(), line2.point() + 2 * line2.direction());
    }