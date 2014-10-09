#include "maze.h"

namespace maze
{
	/* Create an empty maze - allocate space for cells etc */
	maze::Maze::Maze(unsigned height, unsigned width)
	{

		/* rows of vectors of cells */
		for(unsigned i = 0; i < height; i++)
		{
			std::vector<maze::Cell *> current_row;

			/* There will be <width> cells initialised */
			for(unsigned j = 0; j < width; j++)
			{
				Cell * new_c = new Cell(i, j);
				current_row.push_back(new_c);
			}


			cells.push_back(current_row);
		}

		this->width = width;
		this->height = height;

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

		return cells[y_position][x_position];
	}

	void maze::Maze::add_pathway(maze::Cell * cell1, maze::Cell * cell2)
	{
		if(cell1 == nullptr || cell2 == nullptr)
			throw maze::MazeError("Cannot add pathway - one or both cells are null");

		maze::Pathway * pathway =  new Pathway(cell1, cell2);
		pathways.push_back(pathway);
		cell1->add_pathway(pathways[pathways.size() - 1]);
		cell2->add_pathway(pathways[pathways.size() - 1]);
	}

	void maze::Maze::add_pathway(maze::Pathway * pathway)
	{
		pathways.push_back(pathway);

		/* Make sure the cells have a pointer to this */
		pathway->get_first_cell()->add_pathway(pathway);
		pathway->get_second_cell()->add_pathway(pathway);


	}

	Maze::~Maze()
	{

		/* rows of vectors of cells */
		for(unsigned i = 0; i < height; i++)
		{
			std::vector<maze::Cell *> * current_row = &cells[i];

			/* There will be <width> cells initialised */
			for(unsigned j = 0; j < width; j++)
			{
				delete (*current_row)[j];
			}
		}

		/* Pathways */

		for(Pathway * pathway_ptr : pathways)
		{
			delete pathway_ptr;
		}
	}

}
