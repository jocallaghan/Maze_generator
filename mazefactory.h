#pragma once

#include "maze.h"
#include <stdexcept>
#include <string>

namespace maze
{
	class MazeFactory<class T>
	{
		public:
			virtual std::shared_ptr<class T> make_maze();
	};

	class CannotGenerateMaze : public std::runtime_error
	{
		public:
			CannotGenerateMaze(const std::string& message)
				: std::runtime_error("Cannot generate maze: " +
					message) {};
	};
}
