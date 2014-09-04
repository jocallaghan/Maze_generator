#pragma once

#include "cell.h"
#include <vector>

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
			maze::Cell * get_second_cell() { return cell1; };
	};
}
