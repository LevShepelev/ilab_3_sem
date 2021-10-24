#pragma once

#include <cmath>
#include <istream>
#include <ostream>

namespace geom{

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
bool operator  == (const Vector& left, const Vector& right);
Vector operator + (const Vector& left, const Vector& right);
Vector operator - (const Vector& left, const Vector& right);
Vector operator * (double left, const Vector& right);
Vector operator * (const Vector& left, double right);
double operator * (const Vector& left, const Vector& right);
Vector Vect_mul   (const Vector& left, const Vector& right);
double distance   (const Vector& left, const Vector& right);
double Comb_mul   (const Vector& first, const Vector& second, const Vector& third);
double Modul      (const Vector& left);
double sqr_length (const Vector& left);

inline std::istream& operator >> (std::istream& stream, Vector& right)       {return stream >> right.x >> right.y >> right.z;}
inline std::ostream& operator << (std::ostream& stream, const Vector& right) {return stream << '(' << right.x << ", "<< right.y << ", "<< right.z << ')' << std::endl;}
}
