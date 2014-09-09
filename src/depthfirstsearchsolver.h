#pragma once


#include "maze.h"
#include "Solvingstrategy.h"

namespace maze
{
	class DepthFirstSearchSolver : SolvingStrategy
	{
        maze::Maze * maze;

		public:
			void solve_maze() override;
            DepthFirstSearchSolver(maze::Maze & maze) {};
            ~DepthFirstSearchSolver() {};
	};
}
