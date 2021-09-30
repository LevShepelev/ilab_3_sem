#include "Geometry.h"

int main()
    {
    int N = 0;
    bool already_searched_triangles[N] = {false};
    std::cin >> N;
    Triangle *triangles[N];

    for (int i = 0; i < N; i++)
        {
        Vector p1, p2, p3;
        std::cin >> p1 >> p2 >> p3;
        triangles[i] = new Triangle(p1, p2, p3);
        }

    for (int i = 0; i < N; i++)
        {
        if (already_searched_triangles[i] == false)
            for (int j = 0; j < N; j++)
                {
                if (i != j)
                    if (Triangle_crossing(*triangles[i], *triangles[j]))
                        {
                        std::cout << i << " " << j << " ";
                        already_searched_triangles[j] = true;
                        already_searched_triangles[i] = true;
                        break;
                        }
                }
        }
        
    std::cout << std::endl;
    for (int i = 0; i < N; i++)
        delete triangles[i];
    }