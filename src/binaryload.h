#pragma once

#include "maze.h"
#include "mazefactory.h"
#include <string>
#include <iostream>
#include <fstream>
#include <climits>

namespace maze
{
	class BinaryLoad : public MazeFactory
	{
		std::string file_path;

		public:
			BinaryLoad(std::string file_path_):
				file_path(file_path_) {};
			virtual std::unique_ptr<maze::Maze> make_maze() override;
	};
}
