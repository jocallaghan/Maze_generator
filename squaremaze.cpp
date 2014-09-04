#include "squaremaze.h"

namespace maze
{
	maze::SquareMaze::SquareMaze(unsigned height, unsigned width)
	{
		/* Initialise outer vector of cells (y-dimention) */
		cells.resize(height);

		/* Initilise rows of vectors of cells */
		for(unsigned i = 0; i < height; i++)
		{
			std::vector<maze::Cell> current_row;
			current_row.resize(width);
			/* There will be <width> cells initialised */
			cells.push_back(current_row);
		}

	}

	maze::Cell * maze::SquareMaze::get_cell(unsigned x_position, unsigned y_position)
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

	void maze::SquareMaze::add_pathway(maze::Cell & cell1, maze::Cell & cell2)
	{
		maze::Pathway pathway = Pathway(&cell1, &cell2);
		pathways.push_back(pathway);

		cell1.add_pathway(pathway);
		cell2.add_pathway(pathway);
	}

}
