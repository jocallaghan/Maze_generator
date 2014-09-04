#include "svgsave.h"


namespace maze
{
	virtual void persist_maze()
	{
		std::fstream output(file_name,std::fstream::out | std::fstream::trunc);

 		if(!output.is_open())
 		{
			/* Error opening file */
 			throw maze::CannotPersistMaze("Could not open file");
 		}

 		/* header */
 		unsigned long box_width = CELL_SIZE_PIXELS * maze->get_width();
 		unsigned long box_height = CELL_SIZE_PIXELS * maze->get_height();
 		output << "<svg  width='" << box_width << "' ";
 		output << "height='" << box_height << "' ";
 		output << "xmlns='http://www.w3.org/2000/svg'>" << "\n";

 		/* box */
 		output << "<rect width='" << box_width << "' height='" << box_height;
 		output << "' style='fill: black' />" << "\n";

 		/* Edges/pathways */
 		for(auto & pathway : maze->get_pathways())
 		{
 			unsigned long x;
 			unsigned long y;
 			unsigned long current_path_width;
 			unsigned long current_path_height;

 			maze::Cell * first_cell = pathway.get_first_cell();
 			maze::Cell * second_cell = pathway.get_second_cell();
 			

 			/* Dimentions depends on the edges/pathways - some in reverse order 
 			(right to left etc) so first we determine which cell is first,
 			then we can work out how to make the rectangle */
 			if(first_cell.get_x_position() < second_cell.get_x_position())
 			{
 				x = first_cell.get_x_position() * CELL_SIZE_PIXELS + WALL_WIDTH;
 				current_path_width = (second_cell.get_x_position() - first_cell.get_x_position() + 1) * CELL_SIZE_PIXELS 
 				- (2 * WALL_WIDTH);
 			}
 			else
 			{
 				x = second_cell.get_x_position() * CELL_SIZE_PIXELS + WALL_WIDTH;
 				current_path_width = (first_cell.get_x_position() - second_cell.get_x_position() + 1) * CELL_SIZE_PIXELS 
 				- (2 * WALL_WIDTH);
 			}

 			if(first_cell.get_y_position() < second_cell.get_y_position())
 			{
 				y = first_cell.get_y_position() * CELL_SIZE_PIXELS + WALL_WIDTH;
 				current_path_height = (second_cell.get_y_position() - first_cell.get_y_position() + 1) * CELL_SIZE_PIXELS
 				- (2 * WALL_WIDTH);
 			}
 			else
 			{
 				y = second_cell.get_y_position() * CELL_SIZE_PIXELS + WALL_WIDTH;
 				current_path_height = (first_cell.get_y_position() - second_cell.get_y_position() + 1) * CELL_SIZE_PIXELS
 				- (2 * WALL_WIDTH);
 			}

 			output << "<rect style='";
 			if(pathway.is_in_solved_pathway())
 				output << SOLVED_PATHWAY_COLOR;
 			else
 				output << PATHWAY_COLOR;
 			output << "' ";
 			output << " x='" << x;
 			output << "' y='" << y;
 			output << "' width='" << current_path_width;
 			output << "' height='" << current_path_height << "'/>" << "\n";
 		}

 		/* Entry and exit paths */
 		output << "<rect style='fill:rgb(255,255,255)' ";
 		output << " x='0' y='" << WALL_WIDTH << "' width='" << PATH_WIDTH;
 		output << "' height='" << PATH_WIDTH << "'/>" << "\n";

 		output << "<rect style='fill:rgb(255,255,255)' ";
 		output << " x='" << (box_width - PATH_WIDTH)  << "' y='";
 		output << (box_height - PATH_WIDTH - WALL_WIDTH) << "' width='";
 		output << PATH_WIDTH;
 		output << "' height='" << PATH_WIDTH << "'/>" << "\n";

 		/* footer */
 		output << "</svg>" << "\n";

 		output.close();
 	}
}
