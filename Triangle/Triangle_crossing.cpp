#include "Triangles_functions.h"

int main()
    {
    int N = 0;
    std::cin >> N;
    std::vector<geom::Triangle> triangles;
    bool crossing_triangles[N];
    for (int i = 0; i < N; i++)
        {
        geom::Vector p1, p2, p3;
        std::cin >> p1 >> p2 >> p3;
        triangles.push_back(geom::Triangle(p1, p2, p3, i));
        crossing_triangles[i] = false;
        }

    std::sort(triangles.begin(), triangles.end(), [] (const geom::Triangle& tr1, const geom::Triangle& tr2) { if (tr1.min_coord(0) - tr2.min_coord(0) > geom::epsilon) 
                                                                                                                return true;
                                                                                                              else return false; });
    for (int i = 0; i < N - 1; i++)
        for (int j = i + 1; j < N; j++)
            if (geom::Will_we_compare(triangles, i, j) && geom::Triangle_crossing(triangles[j], triangles[i]))
                {
                crossing_triangles[triangles[i].number()] = true;
                crossing_triangles[triangles[j].number()] = true;
                }
            
    for (int i = 0; i < N; i++)
        {
        if (crossing_triangles[i] == true)
            std::cout << i << std::endl;
        }
    }