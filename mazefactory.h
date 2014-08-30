#pragma once

#include "maze.h"
#include <string>

namespace maze
{
	class MazeFactory
	{
		public:
			virtual maze::Maze make_maze(std::string [] args) {};
	}
}
