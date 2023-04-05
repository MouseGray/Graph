#pragma once

#include <limits>

#include "io.h"
#include "tree.h"
#include "vertices_stack.h"

static constexpr auto vertices      = TASK_SIZE;
static constexpr auto tree_vertices = vertices >> 3;
static constexpr auto tree_edges    = tree_vertices - 1;
static constexpr auto max_tree      = MAX_TREE;
static constexpr auto max_edge      = max_tree - tree_edges - 1;

void CreateTree(const std::vector<Edge>* edges, const VPoints* points,
                std::size_t tree_size, std::size_t first, std::size_t last)
{
    Tree tree{tree_size};

    VerticesStack<(tree_vertices << 1)> vertices;

    std::vector<ssize_t> config(tree_size, -1);
    std::size_t pointer = 0;

    auto find_edge = [&] {
        vertices.Pop(pointer << 1);

        for(ssize_t i = config[pointer] + 1; i < edges->size(); ++i)
        {
            if(vertices.IsContain((*edges)[i].A) + vertices.IsContain((*edges)[i].B) == 1)
            {
                config[pointer] = i;
                return true;
            }
        }
        return false;
    };

    auto next_config = [&] {
        while(true)
        {
            if(find_edge())
                break;

            --pointer;

            if(pointer == 0)
                return false;
        }

        return true;
    };

    int min_length = std::numeric_limits<int>::max();
    int min_leaf = std::numeric_limits<int>::max();
    int max_edge = 0;

    for(int i = 0; first != last; ++first, ++i)
    {
        pointer = 1;

        config[0] = first;
        config[1] = -1;

        tree[0].A = (*edges)[first].A;
        tree[0].B = (*edges)[first].B;

        vertices.Push(0, tree[0].A, tree[0].B);

        while(true)
        {
            if(!next_config())
                break;

            tree[pointer].A = (*edges)[config[pointer]].A;
            tree[pointer].B = (*edges)[config[pointer]].B;

            vertices.Push(pointer << 1, tree[pointer].A, tree[pointer].B);

            if(Length(tree, pointer + 1, *points) <= max_tree)
            {
                if(pointer + 1 == tree_size)
                {
                    int length = Length(tree, *points);
                    int leaf = LeafsCount(tree);
                    int edge = MaxEdge(tree, *points);

                    PrintTree(tree, *points);

                    if(std::tie(length, leaf, max_edge)
                       <
                       std::tie(min_length, min_leaf, edge))
                    {
                        min_length = length;
                        min_leaf = min_leaf;
                        max_edge = edge;
                    }
                }
                else
                {
                    ++pointer;
                    config[pointer] = -1;
                }
            }
        }
    }
}
