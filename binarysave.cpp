#include "binarysave.h"

namespace maze
{

	BinarySave(std::shared_ptr<maze::Maze> maze_, std::string file_path_)
	{
		maze = dynamic_cast<maze::SquareMaze *>(maze_.get())),
		file_path = file_path_;
	}

	virtual void maze::BinarySave::persist_maze() override
	{
		std::fstream output(file_path,std::fstream::out | std::fstream::binary |
 		std::fstream::trunc);

 		if(!output.is_open())
 		{
			/* Error opening file */
 			throw maze::CannotPersistMaze("Could not open file");
 		}

 		std::vector<maze::Pathway> * pathways = maze.get()->get_pathways();

		/* Write headers */
 		char number_edges = (char) pathways->size();
 		output.write((char*)&maze->get_width(), sizeof(maze->get_width()));
 		output.write((char*)&maze->get_height(), sizeof(maze->get_height()));
 		output.write((char*)&maze->get_pathways()->size(), maze->get_pathways()->size());

		/* Edges/pathways */
 		for(auto & pathway : pathways)
 		{
			/* x1 */
 			output.write((char*)pathway.get_first_cell().get_x_position(),
 				sizeof(pathway.get_first_cell().get_x_position()));
			/* y1 */
 			output.write((char*)pathway.get_first_cell().get_y_position(),
 				sizeof(pathway.get_first_cell().get_y_position()));
			/* x2 */
 			output.write((char*)pathway.get_second_cell().get_x_position(),
 				sizeof(pathway.get_second_cell().get_x_position()));
			/* y2 */
 			output.write((char*)pathway.get_second_cell().get_y_position(),
 				sizeof(pathway.get_second_cell().get_y_position()));
 		}
 		output.close();
	};

	
}
