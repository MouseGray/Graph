#pragma once

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

#include "vpoint.h"
#include "tree.h"

VPoints ReadFile(const std::string& file, std::size_t& count)
{
    std::string    n, eq;
    unsigned short x, y;

    std::ifstream in{file};

    if(!in.is_open())
        throw std::invalid_argument{"File " + file + " not found"};

    in >> n >> eq >> count;

    if(in.fail())
        throw std::invalid_argument{"Invalid file structure"};

    VPoints points(count);

    auto* xs = points.Xs();
    auto* ys = points.Ys();

    for(int i = 0; i < count; ++i)
    {
        in >> x >> y;

        if(in.fail())
            throw std::invalid_argument{"Invalid file structure"};

        xs[i] = x;
        ys[i] = y;
    }

    return points;
}

void PrintTree(const Tree& edges, const VPoints& points)
{
    static std::mutex mutex;

    std::lock_guard<std::mutex> _{mutex};

    std::cout << "c Width = " << Length(edges, points) <<
                 ", Leaf = " << LeafsCount(edges) << ", Max edge = " << MaxEdge(edges, points) << "\n";
    std::cout << "p edge = " << ((edges.Size() + 1) << 3) <<
                 " " << edges.Size() << "\n";

    for(std::size_t i = 0; i < edges.Size(); ++i)
    {
        auto edge = edges[i];

        std::cout << "e " << edge.A + 1 << " " << edge.B + 1 << "\n";
    }

    std::cout << std::endl;
}
