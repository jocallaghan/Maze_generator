#pragma once

#include "maze.h"
#include "persistencestrategy.h"
#include <memory>
#include <fstream>

namespace maze
{
	class BinarySave : public PersistenceStrategy
	{
		std::shared_ptr<maze::Maze> maze;
		std::string file_path;

		public:
			BinarySave(std::shared_ptr<maze::Maze> maze, std::string file_path);
			virtual void persist_maze() override;
	};
}
