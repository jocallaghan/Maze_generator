#pragma once

#include "maze.h"
#include "mazefactory.h"
#include "disjoint_set.hpp"
#include <string>
#include <stack>
#include <random>
#include <algorithm>

namespace maze
{
	class KruskalGenerator : public MazeFactory
	{
		unsigned height, width, seed;

		public:
			KruskalGenerator(unsigned height_, unsigned width_, unsigned seed_):
				height(height_), width(width_), seed(seed_) {};
			virtual std::unique_ptr<maze::Maze> make_maze() override;
	};
}
