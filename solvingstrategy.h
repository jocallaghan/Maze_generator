#pragma once

#include "maze.h"

namespace maze
{
	class SolvingStrategy
	{
		public:
			virtual void solve_maze(maze::Maze & maze) {};
	}
}
