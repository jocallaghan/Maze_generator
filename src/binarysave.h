#pragma once

#include "maze.h"
#include "persistencestrategy.h"
#include <memory>
#include <fstream>

namespace maze
{
	class BinarySave : public PersistenceStrategy
	{
		maze::Maze * maze;
		std::string file_path;

		public:
			BinarySave(maze::Maze & maze, std::string file_path);
			virtual void persist_maze() override;
	};
}
