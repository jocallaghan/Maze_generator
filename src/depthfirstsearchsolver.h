#pragma once


#include "maze.h"
#include "solvingstrategy.h"
#include <stack>
#include <unordered_set>

namespace maze
{
	class DepthFirstSearchSolver : public SolvingStrategy
	{
        maze::Maze * maze;

		public:
			void solve_maze() override;
            DepthFirstSearchSolver(maze::Maze & maze);
            ~DepthFirstSearchSolver() {};
	};
}
