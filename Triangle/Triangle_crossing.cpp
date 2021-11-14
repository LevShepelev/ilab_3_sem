#include "Triangles_functions.h"

struct Triangle_t {geom::Triangle tr; int number;};

int main()
    {
    int N = 0;
    std::cin >> N;
    std::vector<Triangle_t> triangles;
    bool crossing_triangles[N];
    double extremum[3][2];
    double delta[3];
    int N_segments = pow(N, 0.33333) + 1;
    std::vector<std::vector<int>> parallelepipeds(pow(N_segments, 3));
    for (int i = 0; i < N; i++)
        {
        geom::Vector p1, p2, p3;
        std::cin >> p1 >> p2 >> p3;
        triangles.push_back({geom::Triangle(p1, p2, p3), i});
        for (int j = 0; j < 3; j++)
            {
            extremum[j][0] = std::min(extremum[j][0], triangles.rbegin() -> tr.min_coord(j));
            extremum[j][1] = std::max(extremum[j][1], triangles.rbegin() -> tr.max_coord(j));
            }
        crossing_triangles[i] = false;
        }

    for (int i = 0; i < 3; i++)
        delta[i] = (extremum[i][1] - extremum[i][0]) / N_segments;
        
    for (int t = 0; t < N; t++)
        {
        int edges[3][2];
        for (int f = 0; f < 3; f++)
            {
            if (!geom::Is_zero(delta[f]))
                {
                edges[f][0] = std::min((int) ((triangles[t].tr.min_coord(f) - extremum[f][0]) / delta[f]), N_segments - 1);
                edges[f][1] = std::min((int) ((triangles[t].tr.max_coord(f) - extremum[f][0]) / delta[f]), N_segments - 1);
                }
            else 
                {
                delta[f] = 1;
                edges[f][0] = 0;
                edges[f][1] = 0;
                }
            }

        for (int i = edges[0][0]; i <= edges[0][1]; i++)
            for (int j = edges[1][0]; j <= edges[1][1]; j++)
                for (int k = edges[2][0]; k <= edges[2][1]; k++)
                    parallelepipeds[i * N_segments * N_segments + j * N_segments + k].push_back(triangles[t].number);
        }

    for (int i = 0; i < pow(N_segments, 3) ; ++i)
        {
        for (int j = 0; j != parallelepipeds[i].size(); ++j)
            for (int k = j + 1; k != parallelepipeds[i].size(); ++k)
                if (geom::Triangle_crossing(triangles[parallelepipeds[i][j]].tr, triangles[parallelepipeds[i][k]].tr))
                    {
                    crossing_triangles[parallelepipeds[i][j]] = true;
                    crossing_triangles[parallelepipeds[i][k]] = true;
                    }
                
        }
        
    for (int i = 0; i != N; ++i)
        {
        if (crossing_triangles[i] == true)
            std::cout << i << std::endl;
        }
    }