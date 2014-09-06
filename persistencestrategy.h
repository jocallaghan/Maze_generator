#pragma once

#include "maze.h"
#include <string>
#include <stdexcept>

namespace maze
{
	class PersistenceStrategy
	{
		public:
			virtual void persist_maze() = 0;
			PersistenceStrategy() {};
			~PersistenceStrategy() {};

	};

	class CannotPersistMaze : public std::runtime_error
	{
		public:
			CannotPersistMaze(const std::string& message) : std::runtime_error("Cannot persist maze: " + message) {};
	};
}
