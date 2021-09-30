#include <istream>
#include <iostream>
#include <ostream>
#include <cmath>
#include <vector>

class Vector;
class Line;
class Plane;
class Triangle;
bool Is_zero(double value);
bool Triangle_crossing(Triangle tr1, Triangle tr2);
std::vector<Vector> Triangle_and_line_crossing(Line line, Triangle triangle);
Vector Intersection_point_on_plane(const Line& line1, const Line& line2, Plane plane);

class Vector
    {
    public:
    double x;
    double y;
    double z;
    Vector(){}
    Vector(double px, double py, double pz) : x(px), y(py), z(pz) {}
    bool Is_valid() const;
    bool Is_point_between_other_points(Vector p1, Vector p2) const;
    };

bool operator  == (const Vector& left, const Vector& right)  {return (Is_zero(left.x - right.x) && Is_zero(left.y - right.y) && Is_zero(left.z - right.z));}
Vector operator + (const Vector& left, const Vector& right)  {return Vector(left.x + right.x, left.y + right.y, left.z + right.z);}
Vector operator - (const Vector& left, const Vector& right)  {return Vector(left.x - right.x, left.y - right.y, left.z - right.z);}
Vector operator * (double left, const Vector& right)         {return Vector(left * right.x, left * right.y, left * right.z);}
Vector operator * (const Vector& left, double right)         {return Vector(right * left.x, right * left.y, right * left.z);}
double operator * (const Vector& left, const Vector& right)  {return left.x * right.x + left.y * right.y + left.z * right.z;}
Vector Vect_mul   (const Vector& left, const Vector& right)  {return Vector(left.y * right.z - left.z * right.y, -left.x * right.z + left.z * right.x, left.x * right.y - left.y * right.x);} //[V1 x V2]
double distance   (const Vector& left, const Vector& right)  {return sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2) + pow(left.z - right.z, 2));}
double Comb_mul   (const Vector& first, const Vector& second, const Vector& third) {return (first * Vect_mul(second, third));}

std::istream& operator >> (std::istream& stream, Vector& right)       {return stream >> right.x >> right.y >> right.z;}
std::ostream& operator << (std::ostream& stream, const Vector& right) {return stream << '(' << right.x << ", "<< right.y << ", "<< right.z << ')' << std::endl;}


bool Vector::Is_point_between_other_points(Vector p1, Vector p2) const
    {
    if (*this == p1 || *this == p2)
        return true;
    if ((*this).Is_valid() && p1.Is_valid() && p2.Is_valid())
        {
        if (Is_zero(distance(*this, p1) + distance(*this, p2) - distance(p1, p2)))
            return true;
        }
    return false;
    }

bool Vector::Is_valid() const
    {
    if (std::isfinite(x) && std::isfinite(y) && std::isfinite(z))
        return true;
    else return false;
    }


class Plane
    {
    public:
    Vector N;
    double A, B, C, D;
    Plane(Vector p1, Vector p2, Vector p3);
    Plane() : A(0), B(0), C(0), D(0) {}
    };
std::ostream& operator << (std::ostream& stream, const Plane& plane) {return stream << "A = " << plane.A << "B = " << plane.B << "C = " << plane.C << std::endl;}

Plane::Plane(Vector p1, Vector p2, Vector p3)
    {
    A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
    B = -(p2.x - p1.x) * (p3.z - p1.z) + (p2.z - p1.z) * (p3.x - p1.x);
    C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    D = -p1.x * A - p1.y * B - p1.z * C;
    N = Vector(A, B, C);
    }

class Line
    {
    public:
    Vector point, direction;
    Line(){}
    Line(Vector p1, Vector p2);
    Line(Plane first, Plane second);
    };
std::ostream& operator << (std::ostream& stream, const Line& line) {return stream << "point = " << line.point << "direction = " << line.direction << std::endl;}


Line::Line(Plane first, Plane second) // Line constructor, return crossing line of two planes
    {
    direction = Vect_mul(first.N, second.N);
    if (!(direction == Vector(0, 0, 0)))
        {
        double a = ((-second.D) * first.N * second.N + first.D * second.N * second.N) / ((first.N * second.N) * (first.N * second.N) - (first.N * first.N) * (second.N * second.N));
        double b = ((-first.D) * first.N * second.N + second.D * first.N * first.N) / ((first.N * second.N) * (first.N * second.N) - (first.N * first.N) * (second.N * second.N)); // Geometric Tools for Computer Graphics page 531
        point = first.N * a + second.N  * b;
        }
    else if ((first.A != 0 && Is_zero(-first.D / first.A * second.A + second.D)) || (first.B != 0 && Is_zero(-first.D / first.B * second.B + second.D)) || (first.C != 0 && Is_zero(-first.D / first.C * second.C + second.D)))
        point = Vector (nan(""), nan(""), nan("")); //Planes are parallel, we cant create crossing line"
    else
        point = Vector(nan(""), nan(""), nan("")); //Planes are parallel, we cant create crossing line"
    }

Line::Line(Vector p1, Vector p2)
    {
    direction = p2 - p1;
    point = p1;
    }

class Triangle
    {
    public:
    Triangle(){}
    Triangle(Vector p1, Vector p2, Vector p3);
    const Vector p1_, p2_, p3_;
    Plane plane;
    Line line1_, line2_, line3_;
    };

Triangle::Triangle(Vector p1, Vector p2, Vector p3) : p1_(p1), p2_(p2), p3_(p3), plane(p1, p2, p3)
    {
    plane = Plane(p1_, p2_, p3_);
    line1_ = Line(p1_, p2_);
    line2_ = Line(p2_, p3_);
    line3_ = Line(p3_, p1_);
    }


Vector Intersection_point_on_plane(const Line& line1, const Line& line2, Plane plane) // The function searhces crossing point of two lines that lay in one plane
    {
    if (Vect_mul(line1.direction, line2.direction) == Vector(0, 0, 0))
        return Vector(nan(""), nan(""), nan("")); //Lines are parallel, we cannot choose one point
    else 
        {
        Vector shift_point; //If plane goes through (0, 0, 0) we have to move starting point, shift_point is our shifting
        if (Is_zero(plane.D))
            shift_point = plane.N;
        else shift_point = Vector(0, 0, 0);
        double s = Comb_mul(line2.point - shift_point, line1.point - shift_point, line1.direction) / Comb_mul(line2.point - shift_point, line2.direction, line1.direction);
        return Vector(line2.point.x + s * line2.direction.x, line2.point.y + s * line2.direction.y, line2.point.z + s * line2.direction.z);
        }
    }

bool Triangle_crossing(Triangle tr1, Triangle tr2) // The function get segments and research theirs mutual arrangement
    {
    Line crossing_line(tr1.plane, tr2.plane);
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
    Vector p1 = Intersection_point_on_plane(line, triangle.line1_, triangle.plane);
    Vector p2 = Intersection_point_on_plane(line, triangle.line2_, triangle.plane);
    Vector p3 = Intersection_point_on_plane(line, triangle.line3_, triangle.plane);
    if (p1.Is_point_between_other_points(triangle.p1_, triangle.p2_) || p1.Is_point_between_other_points(triangle.p2_, triangle.p3_) || p1.Is_point_between_other_points(triangle.p3_, triangle.p1_))
        segment.push_back(p1);

    if (p2.Is_point_between_other_points(triangle.p1_, triangle.p2_) || p2.Is_point_between_other_points(triangle.p2_, triangle.p3_) || p2.Is_point_between_other_points(triangle.p3_, triangle.p1_))
        segment.push_back(p2);


    if ((p3.Is_point_between_other_points(triangle.p1_, triangle.p2_) || p3.Is_point_between_other_points(triangle.p2_, triangle.p3_) || p3.Is_point_between_other_points(triangle.p3_, triangle.p1_)) && segment.size() < 2)
        segment.push_back(p3);

    return segment;
    }

bool Is_zero(double value)
    {
    const double epsilon = 1e-5;
    if (-epsilon < value && value < epsilon)
        return 1;
    else return 0;
    }