#pragma once

#include "cell.h"
#include "pathway.h"
#include <vector>

namespace maze
{
	

	class Maze
	{
		std::vector<std::vector<maze::Cell>> cells;
		std::vector<maze::Pathway *> pathways;
		unsigned height, width;

		public:
			Maze(unsigned height, unsigned width);
			Maze(): height(0), width(0) {};

			unsigned get_height() { return height; };
			unsigned get_width() { return width; }
			maze::Cell * get_cell(unsigned x_position, unsigned y_position);
			void add_pathway(maze::Cell * cell1, maze::Cell * cell2);
			std::vector<maze::Pathway *> * get_pathways() { return &pathways; };

	};
}
