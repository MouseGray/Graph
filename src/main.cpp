#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <algorithm>

#include <thread>
#include <numeric>
#include <unistd.h>
#include "algorithm.h"

int main(int argc, char *argv[])
{
    constexpr auto edges_count = 7;

    if(argc < 2)
    {
        std::cout << "STree <file>" << std::endl;
        return 0;
    }

    try
    {
        std::size_t count;

        auto cores_count = std::thread::hardware_concurrency();

        auto points = ReadFile(argv[1], count);

        if(cores_count == 0)
        {
            std::cout << "Hardware concurrency not supported" << std::endl;
            return 1;
        }

        std::vector<Edge> edges;

        for(uint16_t i = 0; i < count; ++i)
        {
            for(uint16_t j = i + 1; j < count; ++j)
            {
                uint16_t distance = std::abs(points.Xs()[i] - points.Xs()[j]) +
                                    std::abs(points.Ys()[i] - points.Ys()[j]);

                if(distance <= max_edge)
                {
                    edges.push_back({i, j, distance});
                }
            }
        }

        std::sort(edges.begin(), edges.end(), [](const Edge& lhs, const Edge& rhs){
            return lhs.Length > rhs.Length;
        });

        std::cout << "count: " << edges.size() << std::endl;

        std::vector<std::thread> threads;

        std::size_t step = edges.size() / cores_count;

        for(std::size_t i = 0; i < cores_count; ++i)
        {
            if(i + 1 < cores_count)
                threads.emplace_back(&CreateTree, &edges, &points, std::size_t{tree_edges}, i*step, (i + 1)*step);
            else
                threads.emplace_back(&CreateTree, &edges, &points, std::size_t{tree_edges}, i*step, edges.size());
        }

        for(auto& thread : threads)
            thread.join();
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}


