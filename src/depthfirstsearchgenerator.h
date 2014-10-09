#pragma once

#include "maze.h"
#include "mazefactory.h"
#include <string>
#include <stack>
#include <random>

namespace maze
{
	class DepthFirstSearchGenerator : public MazeFactory
	{
		unsigned height, width, seed;

		public:
			DepthFirstSearchGenerator(unsigned height_, unsigned width_, unsigned seed_):
				height(height_), width(width_), seed(seed_) {};
			virtual std::unique_ptr<maze::Maze> make_maze() override;
	};
}
