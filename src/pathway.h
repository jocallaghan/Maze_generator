#pragma once

#include "cell.h"
#include <vector>
#include <functional>



namespace maze
{
	class Cell;

	class Pathway
	{
		maze::Cell * cell1, * cell2;
		bool in_solved_pathway;

		public:
			Pathway(maze::Cell * cell_arg1, maze::Cell * cell_arg2): cell1(cell_arg1),
				cell2(cell_arg2), in_solved_pathway(false) {};

			bool is_in_solved_pathway() { return in_solved_pathway; };
			void set_solved_pathway() { in_solved_pathway = true; };
			maze::Cell * get_first_cell() { return cell1; };
			maze::Cell * get_second_cell() { return cell2; };
			maze::Cell * get_other_cell(maze::Cell * cell);
			~Pathway() {};

			
	};
}

/* Adapted from examples by Nijansen on Stack Overflow http://stackoverflow.com/a/18098536 (accessed 9/9/14) 
   and by Ken Bloom http://stackoverflow.com/a/2634715 (accessed 9/9/14) */

namespace std
{
	template <>
	struct hash< maze::Pathway * >
	{
		std::size_t operator()(maze::Pathway * const & pathway) const noexcept
		{
			return std::hash<std::size_t>()((std::size_t)pathway);
		}
	};
}
