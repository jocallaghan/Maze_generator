#include "binarysave.h"
/*#include <iostream>*/

namespace maze
{

	maze::BinarySave::BinarySave(maze::Maze & maze, std::string file_path)
	{
		this->maze = &maze,
		this->file_path = file_path;
	}

	/* Persists a maze into a binary file */
	void maze::BinarySave::persist_maze()
	{
		std::fstream output(file_path,std::fstream::out | std::fstream::binary | std::fstream::trunc);

 		if(!output.is_open())
 		{
			/* Error opening file */
 			throw maze::CannotPersistMaze("Could not open file");
 		}

 		std::vector<maze::Pathway *> * pathways = maze->get_pathways();

		/* Write headers */
 		const unsigned number_edges = pathways->size();
		const unsigned height = maze->get_height();
		const unsigned width = maze->get_width();
		output.write((char*)&width, sizeof(width));
		output.write((char*)&height, sizeof(height));
		output.write((char*)&number_edges, sizeof(number_edges));


		/*std::cout << "Width: " << width << ", height: " << height << ", number_edges: ";
 		std::cout << number_edges << "\n";*/

			
		/* Edges/pathways */
 		for(maze::Pathway * pathway : *pathways)
 		{
			const unsigned x1 = pathway->get_first_cell()->get_x_position();
			const unsigned x2 = pathway->get_second_cell()->get_x_position();
			const unsigned y1 = pathway->get_first_cell()->get_y_position();
			const unsigned y2 = pathway->get_second_cell()->get_y_position();

			/* x1 */
			output.write((char*)&x1, sizeof(x1));
			/* y1 */
			output.write((char*)&y1, sizeof(y1));
			/* x2 */
			output.write((char*)&x2, sizeof(x2));
			/* y2 */
			output.write((char*)&y2, sizeof(y2));
 		}
 		output.close();
	}

	
}
