#pragma once

#include "Line.h"
#include "Plane.h"
#include "Vector.h"

class Line;
class Plane;
class Triangle;

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

