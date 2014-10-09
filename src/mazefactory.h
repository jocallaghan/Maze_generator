#pragma once

#include "maze.h"
#include <stdexcept>
#include <string>
#include <memory>

namespace maze
{
	class MazeFactory
	{
		public:
			virtual std::unique_ptr<maze::Maze> make_maze() = 0;
			MazeFactory() {};
			~MazeFactory() {};

			
	};

	class CannotGenerateMaze : public std::runtime_error
	{
		public:
			CannotGenerateMaze(const std::string& message)
				: std::runtime_error("Cannot generate maze: " +
					message + "\n") {};
	};
}
