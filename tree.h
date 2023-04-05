#pragma once

#include <set>

#include "edge.h"
#include "vpoint.h"

using Tree = Edges;

int Distance(uint16_t A, uint16_t B, const VPoints& points)
{
    return std::abs(points.Xs()[A] - points.Xs()[B]) +
           std::abs(points.Ys()[A] - points.Ys()[B]);
}

int Length(const Tree& edges, const VPoints& points)
{
    int length = 0;

    for(int i = 0; i < edges.Size(); ++i)
    {
        length += Distance(edges[i].A, edges[i].B, points);
    }

    return length;
}

int Length(const Tree& edges, std::size_t size, const VPoints& points)
{
    int length = 0;

    for(int i = 0; i < size; ++i)
    {
        length += Distance(edges[i].A, edges[i].B, points);
    }

    return length;
}

int MaxEdge(const Tree& edges, const VPoints& points)
{
    int max_edge = 0;

    for(int i = 0; i < edges.Size(); ++i)
    {
        auto distance = Distance(edges[i].A, edges[i].B, points);

        if(distance > max_edge)
            max_edge = distance;
    }

    return max_edge;
}

int LeafsCount(const Tree& edges)
{
    int leaf_count = 0;
    std::set<std::size_t> vertices;

    for(std::size_t i = 0; i < edges.Size(); ++i)
    {
        auto edge = edges[i];

        vertices.insert(edge.A);
        vertices.insert(edge.B);
    }

    for(std::size_t v : vertices)
    {
        int count = 0;
        for(std::size_t i = 0; i < edges.Size(); ++i)
        {
            auto edge = edges[i];

            if(edge.A == v || edge.B == v)
                ++count;
        }

        if(count == 1)
            ++leaf_count;
    }

    return leaf_count;
}
