#pragma once

#include "squaremaze.h"
#include "persistencestrategy.h"

namespace maze
{
	class BinarySave : public PersistenceStrategy
	{
		maze::SquareMaze * maze;
		std::string file_path;

		public:
			BinarySave(std::shared_ptr<maze::Maze> maze_, std::string file_path_);
			virtual void persist_maze();
	};
}
