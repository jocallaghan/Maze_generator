#pragma once


#include "maze.h"
#include "solvingstrategy.h"
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include "helper.h"

#define DISTANCE_BETWEEN_ADJ_CELLS 1

namespace maze
{
	class AStarSolver : public SolvingStrategy
    {
        maze::Maze * maze;

        public:
            void solve_maze() override;
            AStarSolver(maze::Maze & maze);
            ~AStarSolver() {};

        private:
            unsigned heuristic_estimate(maze::Cell & cell, maze::Maze & maze);
    };

    typedef struct Priority_and_cell
    {
        maze::Cell * cell;
        double priority;

        Priority_and_cell(maze::Cell * cell, double priority): cell(cell), priority(priority) {};
    } Priority_and_cell;

}

/* specialisation of the less functor drawn from example given from Stick it to THE MAN on
Stack Overflow (https://stackoverflow.com/q/2282349 accessed 4/10/14) */
namespace std {
    template<>
    struct less<maze::Priority_and_cell>
    {
        bool operator()(const maze::Priority_and_cell& pcell1, const maze::Priority_and_cell& pcell2) const
        {
            return pcell1.priority < pcell2.priority;
        }
    };
}