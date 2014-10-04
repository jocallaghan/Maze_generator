#pragma once


#include "maze.h"
#include "solvingstrategy.h"
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <list>

namespace maze
{
	class BreadthFirstSearchSolver : SolvingStrategy
    {
        maze::Maze * maze;

        public:
            void solve_maze() override;
            BreadthFirstSearchSolver(maze::Maze & maze);
            ~BreadthFirstSearchSolver() {};

        private:
            void build_solved_pathway(std::unordered_map<maze::Cell *, maze::Pathway *, std::hash<maze::Cell *> > * path_map, 
                maze::Cell * first_cell, maze::Cell * last_cell);
    };
}
