#pragma once

#include "pathway.h"
#include <vector>
#include <functional>

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
			~Cell() {};
			unsigned get_x_position() { return x_position; };
			unsigned get_y_position() { return y_position; }
			void add_pathway(maze::Pathway * pathway);
			std::vector<maze::Pathway *> * get_pathways() 
				{ return &pathways; };
			bool has_pathway() { return !pathways.empty(); };
	};
}

/* Adapted from examples by Nijansen on Stack Overflow http://stackoverflow.com/a/18098536 (accessed 9/9/14) 
   and by Ken Bloom http://stackoverflow.com/a/2634715 (accessed 9/9/14) */

namespace std
{
	template <>
	struct hash< maze::Cell * >
	{
		std::size_t operator()(maze::Cell * const & cell) const noexcept
		{
			return std::hash<std::size_t>()((std::size_t)cell);
		}
	};
}

