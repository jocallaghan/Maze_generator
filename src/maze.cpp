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
		if(cell1 == nullptr || cell2 == nullptr)
		{
			std::cerr << "error creating path\n";
		}

		maze::Pathway * pathway =  new Pathway(cell1, cell2);
		pathways.push_back(pathway);
		cell1->add_pathway(pathways[pathways.size() - 1]);
		cell2->add_pathway(pathways[pathways.size() - 1]);


		/*std::cerr << "Numpathways: " << pathways.size() << "\n";
		std::cerr << "x1: " << pathways.back()->get_first_cell()->get_x_position() 
			<< ", y1: " << pathways.back()->get_first_cell()->get_y_position()
			<< ", x2: " << pathways.back()->get_second_cell()->get_x_position() 
			<< ", y2: " << pathways.back()->get_second_cell()->get_y_position() << "\n";*/


	}

}
