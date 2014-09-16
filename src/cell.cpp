#include "cell.h"

namespace maze
{
	maze::Cell::Cell(unsigned y_position, unsigned x_position)
	{
		this->x_position = x_position;
		this->y_position = y_position;
	}

	void maze::Cell::add_pathway(maze::Pathway * pathway)
	{
		pathways.push_back(pathway);
	}
}
