#pragma once

#include "pathway.h"
#include <vector>

namespace maze
{
	class Pathway;

	class Cell
	{
		unsigned x_position, y_position;
		std::vector<maze::Pathway *> pathways;

		public:
			Cell(unsigned y_position, unsigned x_position);
			Cell(): x_position(0), y_position(0) {};
			unsigned get_x_position() { return x_position; };
			unsigned get_y_position() { return y_position; }
			void add_pathway(maze::Pathway & pathway);
			std::vector<maze::Pathway *> * get_pathways() 
				{ return &pathways; };
			bool has_pathway() { return !pathways.empty(); };
	};
}
