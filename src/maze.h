#pragma once

#include "cell.h"
#include "pathway.h"
#include <vector>
#include <stdexcept>

#define NUMBER_WALLS_PER_CELL 4



namespace maze
{
	

	class Maze
	{
		std::vector<std::vector<maze::Cell *>> cells;
		std::vector<maze::Pathway *> pathways;
		unsigned height, width;

		public:
			Maze(unsigned height, unsigned width);
			Maze(): height(0), width(0) {};
			~Maze();

			unsigned get_height() { return height; };
			unsigned get_width() { return width; }
			maze::Cell * get_cell(unsigned x_position, unsigned y_position);
			void add_pathway(maze::Cell * cell1, maze::Cell * cell2);
			void add_pathway(maze::Pathway * pathway);
			std::vector<maze::Pathway *> * get_pathways() { return &pathways; };
			std::vector<std::vector<maze::Cell *>> * get_cells() { return &cells; };
			unsigned long max_num_pathways() { return (unsigned long)height * width * NUMBER_WALLS_PER_CELL; };
			unsigned long num_cells() { return (unsigned long)height * width; };
			maze::Cell * get_entry_cell() { return get_cell(0, 0); } /* Entry at 0,0 */
			maze::Cell * get_exit_cell() { return get_cell(width - 1, height - 1); } /* Exit at last indexes */


	};

	class MazeError : public std::runtime_error
	{
		public:
			MazeError(const std::string& message) : std::runtime_error("Maze error: " + message) {};
	};
}
