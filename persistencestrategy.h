#pragma once

#include "maze.h"
#include <string>

namespace maze
{
	class PersistenceStrategy
	{
		public:
			virtual void persist_maze() {};
	};

	class CannotPersistMaze : public std::runtime_error
	{
		public:
			CannotPersistMaze(const std::string& message)
				: std::runtime_error("Cannot persist maze: " +
					message) {};
	};
}
