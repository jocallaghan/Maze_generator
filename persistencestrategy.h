#pragma once

#include "maze.h"

namespace maze
{
	class PersistanceStrategy
	{
		public:
			virtual void persist_maze(maze::Maze & maze) {};
	}
}
