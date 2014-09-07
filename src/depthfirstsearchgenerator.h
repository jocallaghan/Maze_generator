#pragma once

#include "maze.h"
#include "mazefactory.h"
#include <string>
#include <stack>
#include <random>
#include <iostream>

namespace maze
{
	class DepthFirstSearchGenerator : public MazeFactory
	{
		unsigned height, width;
		std::string seed;

		public:
			DepthFirstSearchGenerator(unsigned height_, unsigned width_, std::string seed_):
				height(height_), width(width_), seed(seed_) {};
			virtual std::shared_ptr<maze::Maze> make_maze() override;
	};
}
