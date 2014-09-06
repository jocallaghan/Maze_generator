#include "binarysave.h"

namespace maze
{

	maze::BinarySave::BinarySave(std::shared_ptr<maze::Maze> maze, std::string file_path)
	{
		this->maze = maze,
		this->file_path = file_path;
	}

	void maze::BinarySave::persist_maze()
	{
		std::fstream output(file_path,std::fstream::out | std::fstream::binary | std::fstream::trunc);

 		if(!output.is_open())
 		{
			/* Error opening file */
 			throw maze::CannotPersistMaze("Could not open file");
 		}

 		std::vector<maze::Pathway> * pathways = maze->get_pathways();

		/* Write headers */
 		const char number_edges = (char)pathways->size();
		const char height = (char)maze->get_height();
		const char width = (char)maze->get_width();
		output.write((char*)&width, sizeof(width));
		output.write((char*)&height, sizeof(height));
		output.write((char*)&number_edges, sizeof(number_edges));
			
		/* Edges/pathways */
 		for(maze::Pathway pathway : *pathways)
 		{
			const char x1 = pathway.get_first_cell()->get_x_position();
			const char x2 = pathway.get_second_cell()->get_x_position();
			const char y1 = pathway.get_first_cell()->get_y_position();
			const char y2 = pathway.get_second_cell()->get_y_position();

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
