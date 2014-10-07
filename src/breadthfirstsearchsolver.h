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
	class BreadthFirstSearchSolver : public SolvingStrategy
    {
        maze::Maze * maze;

        public:
            void solve_maze() override;
            BreadthFirstSearchSolver(maze::Maze & maze);
            ~BreadthFirstSearchSolver() {};
    };
}
