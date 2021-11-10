#include "Triangles_functions.h"

namespace geom{

/// \brief The function searhces crossing point of two lines that lay in one plane
Vector Intersection_point_on_plane(const Line& line1, const Line& line2, Plane plane)
    {
    if (Vect_mul(line1.direction(), line2.direction()) == Vector(0, 0, 0) && Is_point_on_line(line1, line2.point()))
        return line2.point(); //Lines are equal

    else if (Vect_mul(line1.direction(), line2.direction()) == Vector(0, 0, 0))
        return Vector(nan(""), nan(""), nan("")); //Lines are parallel, we cannot choose one point

    else 
        {
        Vector shift_point; //If plane goes through (0, 0, 0) we have to move starting point, shift_point is our shifting
        if (Is_zero(plane.D()))
            shift_point = plane.normal();
        else shift_point = Vector(0, 0, 0);
        double s = Comb_mul(line2.point() - shift_point, line1.point() - shift_point, line1.direction()) / Comb_mul(line2.point() - shift_point, line2.direction(), line1.direction());
        return Vector(line2.point().x + s * line2.direction().x, line2.point().y + s * line2.direction().y, line2.point().z + s * line2.direction().z);
        }
    }


/// \brief The function get segments and research theirs mutual arrangement
bool Triangle_crossing(const Triangle& tr1, const Triangle& tr2)
    {
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
        std::cout << crossing_line;
        if  (segment_1.size() == 2 && segment_2.size() == 2 &&
            (segment_1[0].Is_point_between_other_points(segment_2[0], segment_2[1]) || segment_1[1].Is_point_between_other_points(segment_2[0], segment_2[1]) ||
             segment_2[0].Is_point_between_other_points(segment_1[0], segment_1[1]) || segment_2[1].Is_point_between_other_points(segment_1[0], segment_1[1])))
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


/// \brief The function finds out if triangles intersect
bool Triangles_crossing_in_one_plane(Triangle tr1, Triangle tr2)
    {
    std::vector<Vector> segments[3];
    segments[0] = Triangle_and_line_crossing(tr1.line(1), tr2);
    segments[1] = Triangle_and_line_crossing(tr1.line(2), tr2);
    segments[2] = Triangle_and_line_crossing(tr1.line(3), tr2);
    if (Is_point_of_Trinagle_inside_segment(segments[0], 1, tr1) || Is_point_of_Trinagle_inside_segment(segments[1], 2, tr1) || Is_point_of_Trinagle_inside_segment(segments[2], 3, tr1) ||
        Is_point_inside_triangle(tr1.p(1), tr2) || Is_point_inside_triangle(tr2.p(1), tr1)) //second or, third or cases are about full triangle lay in other 
        return true;
    return false;
    }


/// \brief The function searchers intersection of crossing_line and triangle(they are in one plane) and return segments
std::vector<Vector> Triangle_and_line_crossing(Line line, Triangle triangle)
    {
    std::vector<Vector> segment;
    Vector p1 = Intersection_point_on_plane(line, triangle.line(1), triangle.plane());
    Vector p2 = Intersection_point_on_plane(line, triangle.line(2), triangle.plane());
    Vector p3 = Intersection_point_on_plane(line, triangle.line(3), triangle.plane());
    
    if (p1.Is_point_between_other_points(triangle.p(1), triangle.p(2)) || p1.Is_point_between_other_points(triangle.p(2), triangle.p(3)) ||
        p1.Is_point_between_other_points(triangle.p(3), triangle.p(1))  )
        segment.push_back(p1);
        

    if (p2 != p1 && (p2.Is_point_between_other_points(triangle.p(1), triangle.p(2)) || p2.Is_point_between_other_points(triangle.p(2), triangle.p(3)) || 
        p2.Is_point_between_other_points(triangle.p(3), triangle.p(1))) )
        segment.push_back(p2);


    if (p3 != p1 && p3 != p2 && segment.size() < 2 && (p3.Is_point_between_other_points(triangle.p(1), triangle.p(2)) || p3.Is_point_between_other_points(triangle.p(2), triangle.p(3)) || 
        p3.Is_point_between_other_points(triangle.p(3), triangle.p(1))) )
        segment.push_back(p3);
        
    return segment;
    }

/// \brief The funciton finds, is point of triangle inside segment of crossing line of triangle and another triangle
// numb is number (numbe of point in the context of triangle) of first point of segment
bool Is_point_of_Trinagle_inside_segment(std::vector<Vector> segment, int numb, const Triangle& tr)
    {
    if ((segment.size() == 2 && (tr.p(numb).Is_point_between_other_points(segment[0], segment[1]) || tr.p(numb % 3 + 1).Is_point_between_other_points(segment[0], segment[1]))) ||
        (segment.size() == 1 && (tr.p(numb) == segment[0] || tr.p(numb % 3 + 1) == segment[0])))
        return true;
    else return false;
    }


/// \brief The function finds out can two triangles intersect 
bool Will_we_compare(std::vector<Triangle> triangles, int i, int j)
    {
    if  (((triangles[j].min_coord(0) <= triangles[i].max_coord(0))
        &&(triangles[j].min_coord(1) <= triangles[i].max_coord(1))
        &&(triangles[j].min_coord(2) <= triangles[i].max_coord(2)))
        || !(triangles[j].Is_valid()) || !(triangles[i].Is_valid()))    
        return true;
    
    else return false;
    }


/// \brief The function finds out is point inside the triangle, (triangle and point must lay in one plane
bool Is_point_inside_triangle(const Vector& point, const Triangle& tr1)
    {
    if (Is_zero(point * tr1.plane().normal() + tr1.plane().D()))
        {
        double  cb1 = Comb_mul(tr1.plane().normal(), tr1.p(1) - point, tr1.p(2) - point),
                cb2 = Comb_mul(tr1.plane().normal(), tr1.p(2) - point, tr1.p(3) - point),
                cb3 = Comb_mul(tr1.plane().normal(), tr1.p(3) - point, tr1.p(1) - point);
        if ((cb1 >= 0 && cb2 >= 0 && cb3 >= 0) || (cb1 <= 0 && cb2 <= 0 && cb3 <= 0))
            return true;
        else return false; 
        }
    else return false;
    }


/// \brief The function handle invalid cases: (triangle, line), (triangle, point), (line, line), (point, line), (point, point)
bool Triagnle_crossing_invalide_cases(const Triangle& tr1, const Triangle& tr2)
    {
    if (Invalid_case_Trinagle_line(tr1, tr2) || Invalid_case_Trinagle_line(tr2, tr1))
        return true;
            
    if (Invalid_case_two_line(tr1, tr2))
        return true;

    if ((tr1.Is_valid() && !tr2.Is_valid() && Is_point_on_plane(tr1.plane(), tr2.p(1)) && Is_point_inside_triangle(tr2.p(1), tr1)) || //one triangle and point
        (tr2.Is_valid() && !tr1.Is_valid() && Is_point_on_plane(tr2.plane(), tr1.p(1)) && Is_point_inside_triangle(tr1.p(1), tr2)))
        return true;

    if (Invalid_case_line_point(tr1, tr2) || Invalid_case_line_point(tr2, tr1))
        return true;

    if (!tr1.Is_valid() && !tr2.Is_valid() && (tr1.p(1) == tr2.p(1))) //two points
        return true;

    return false;      
    }


bool Invalid_case_line_point(const Triangle& tr1, const Triangle tr2)
    {
    for (int i = 1; i <= 3; i++)
        if (tr1.line(i).Is_valid()) //we suppose tr1 is line, tr2 is point
            {
            for (int j = 1; j < 3; j++)
                {
                if (Is_point_on_line(tr1.line(i), tr2.p(j)) && (tr2.p(j).Is_point_between_other_points(tr1.p(1), tr1.p(2)) 
                    || tr2.p(j).Is_point_between_other_points(tr1.p(2), tr1.p(3)) || tr2.p(j).Is_point_between_other_points(tr1.p(3), tr1.p(1))))
                    return true;
                }
            }
    return false;
    }


bool Invalid_case_Trinagle_line(const Triangle& tr1, const Triangle tr2)
    {
    printf("Invalid: Triangle and line\n");
    for (int i = 1; i <= 3; i++)   //triangle and line
        if (!tr1.Is_valid() && tr2.Is_valid() && tr1.line(i).Is_valid())
            return Triangle_and_line_interesection_in_3D(tr1.line(i), tr2);
    return false;
    }


bool Invalid_case_two_line(const Triangle& tr1, const Triangle& tr2)
    {
    for (int i = 1; i <= 3; i++)   //two lines
        if (tr1.line(i).Is_valid())
            for (int j = 1; j <= 3; j++)
                if (tr2.line(2).Is_valid() && Is_lines_in_one_plane(tr1.line(i), tr2.line(j)))
                    {
                    Vector p = Intersection_point_on_plane(tr1.line(i), tr2.line(j), Search_common_plane(tr1.line(i), tr2.line(j)));
                    if (p.Is_point_between_other_points(tr1.p(i), tr1.p(i % 3 + 1)) && p.Is_point_between_other_points(tr2.p(j), tr2.p(j % 3 + 1))) // j % 3 + 1 is next point to j
                        return true;
                    }
    return false;
    }


/// \brief The function finds out if there's intersecton of line and Triangle in 3D
bool Triangle_and_line_interesection_in_3D(const Line& line, const Triangle& tr)
    {
    printf("Tr and line inter\n");
    if (!line.Is_valid())
        {
        printf("invalid line\n");
        return false;
        }
    double t = (-tr.plane().D() - line.point().x * tr.plane().normal().x - line.point().y * tr.plane().normal().y - line.point().z * tr.plane().normal().z) / (line.direction().x * tr.plane().normal().x + line.direction().y * tr.plane().normal().y + line.direction().z * tr.plane().normal().z);
    return Is_point_inside_triangle(Vector(line.point().x + t * line.direction().x, line.point().y + t * line.direction().y, line.point().z + t * line.direction().z), tr);
    }
}


