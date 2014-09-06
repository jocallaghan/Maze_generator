#include "maze.h"
#include <iostream>

namespace maze
{
	maze::Maze::Maze(unsigned height, unsigned width)
	{

		/* rows of vectors of cells */
		for(unsigned i = 0; i < height; i++)
		{
			std::vector<maze::Cell> current_row;

			/* There will be <width> cells initialised */
			for(unsigned j = 0; j < width; j++)
			{
				Cell new_cell(i, j);
				current_row.push_back(new_cell);
			}


			cells.push_back(current_row);
		}

		this->width = width;
		this->height = height;


		/* for(unsigned i = 0; i < height; i++)
		{

			for (unsigned j = 0; j < width; j++)
			{
				std::cout << "Cell [" << i << "][" << j << "] :: ";
				std::cout << "y_position : " << cells[i][j].get_y_position();
				std::cout << ", x_position : " << cells[i][j].get_x_position();
				std::cout << "\n";
			}
		} */

	}

	maze::Cell * maze::Maze::get_cell(unsigned x_position, unsigned y_position)
	{
		if(x_position >= width)
		{
			return nullptr;
		}

		if(y_position >= height)
		{
			return nullptr;
		}

		return &cells[y_position][x_position];
	}

	void maze::Maze::add_pathway(maze::Cell * cell1, maze::Cell * cell2)
	{
		maze::Pathway pathway = Pathway(cell1, cell2);
		pathways.push_back(pathway);

		cell1->add_pathway(pathway);
		cell2->add_pathway(pathway);
	}

}
