#pragma once

#include "squaremaze.h"
#include <string>
#include <iostream>
#include <memory>

namespace maze
{
	class BinaryLoad : public MazeFactory
	{
		std::string file_path;

		public:
			BinaryLoad(std::string file_path_):
				file_path(file_path_) {};
			virtual std::shared_ptr<maze::Maze> make_maze() override;
	};
}
