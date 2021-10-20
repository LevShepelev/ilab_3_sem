#pragma once

#include <cmath>
#include <istream>
#include <ostream>

const double epsilon = 1e-5;
struct Vector
    {
    public:
    double x;
    double y;
    double z;
    Vector() : x(nan("")), y(nan("")), z(nan("")) {}
    Vector(double px, double py, double pz) : x(px), y(py), z(pz) {}
    bool Is_valid() const;
    bool Is_point_between_other_points(Vector p1, Vector p2) const;
    double operator []  (int coord_number) const;
    };

bool Is_zero(double value);
bool operator  == (const Vector& left, const Vector& right)  { return (Is_zero(left.x - right.x) && Is_zero(left.y - right.y) && Is_zero(left.z - right.z)); }
Vector operator + (const Vector& left, const Vector& right)  { return Vector(left.x + right.x, left.y + right.y, left.z + right.z); }
Vector operator - (const Vector& left, const Vector& right)  { return Vector(left.x - right.x, left.y - right.y, left.z - right.z); }
Vector operator * (double left, const Vector& right)         { return Vector(left * right.x, left * right.y, left * right.z); }
Vector operator * (const Vector& left, double right)         { return Vector(right * left.x, right * left.y, right * left.z); }
double operator * (const Vector& left, const Vector& right)  { return left.x * right.x + left.y * right.y + left.z * right.z; }
Vector Vect_mul   (const Vector& left, const Vector& right)  { return Vector(left.y * right.z - left.z * right.y, -left.x * right.z + left.z * right.x, left.x * right.y - left.y * right.x); } //[V1 x V2]
double distance   (const Vector& left, const Vector& right)  { return sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2) + pow(left.z - right.z, 2)); }
double Comb_mul   (const Vector& first, const Vector& second, const Vector& third) {return (first * Vect_mul(second, third)); }
double Modul      (const Vector& left) { return sqrt(left.x * left.x + left.y * left.y + left.z * left.z); } 
double sqr_length (const Vector& left) { return left.x * left.x + left.y * left.y + left.z * left.z; }
double Vector::operator []  (int coord_number) const { if (coord_number == 0)      return x;
                                                       else if (coord_number == 1) return y;
                                                       else if (coord_number == 2) return z;
                                                       else return nan(""); }
                                                        


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

bool Is_zero(double value)
    {
    if (-epsilon < value && value < epsilon)
        return 1;
    else return 0;
    }
