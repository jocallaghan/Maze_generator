#include "svgsave.h"

#include <iostream>


namespace maze
{
	void maze::SVGSave::persist_maze()
	{
		std::fstream output(file_path, std::fstream::out | std::fstream::trunc);

 		if(!output.is_open())
 		{
			/* Error opening file */
 			throw maze::CannotPersistMaze("Could not open file");
 		}

 		/* header */
 		unsigned offset = WALL_WIDTH * 2; /* Both sides */
 		unsigned long box_width = CELL_SIZE_PIXELS * maze->get_width() + offset;
 		unsigned long box_height = CELL_SIZE_PIXELS * maze->get_height() + offset;
 		output << "<svg width='" << box_width << "' ";
 		output << "height='" << box_height << "' ";
 		output << "xmlns='http://www.w3.org/2000/svg'>" << "\n";

 		/* box */
 		output << "<rect width='" << box_width << "' height='" << box_height;
 		output << "' style='fill: black' />" << "\n";

 		/* Edges/pathways */

		/* std::vector<maze::Pathway *> solved_pathways; */

 		for(auto & pathway : *maze->get_pathways())
 		{

			/* if (pathway.is_in_solved_pathway())
			{
				We are going to render the solved ones last so that
				the unsolved pathways dont go over these ones - so place a
				pointer in the new vector and skip to next pathway
				solved_pathways.push_back(&pathway);
				continue;
			} */

 			unsigned long x;
 			unsigned long y;
 			unsigned long current_path_width;
 			unsigned long current_path_height;

 			maze::Cell * first_cell = pathway.get_first_cell();
 			maze::Cell * second_cell = pathway.get_second_cell();

 			unsigned x1 = first_cell->get_x_position();
 			unsigned x2 = second_cell->get_x_position();
 			unsigned y1 = first_cell->get_y_position();
 			unsigned y2 = second_cell->get_y_position(); 			

 			/* Dimentions depends on the edges/pathways - some in reverse order 
 			(right to left etc) so first we determine which cell is first,
 			then we can work out how to make the rectangle */
			if (x1 < x2)
 			{
				x = x1 * CELL_SIZE_PIXELS + offset;
				current_path_width = 2 * CELL_SIZE_PIXELS - offset;
					/* (spanning over two cells) */
 			}
 			else if (x1 > x2)
 			{
				x = x2 * CELL_SIZE_PIXELS + offset;
				current_path_width = 2 * CELL_SIZE_PIXELS - offset;
					/* (spanning over two cells) */
 			}
 			else /* equal */
 			{
 				x = x2 * CELL_SIZE_PIXELS + offset;
				current_path_width = CELL_SIZE_PIXELS - offset;
					/* (spanning over one cell) */
 			}

			if (y1 < y2)
 			{
				y = y1 * CELL_SIZE_PIXELS + offset;
				current_path_height = 2 * CELL_SIZE_PIXELS - offset;
					/* (spanning over two cells) */
 			}
 			else if (y1 > y2)
 			{
				y = y2 * CELL_SIZE_PIXELS + offset;
				current_path_height = 2 * CELL_SIZE_PIXELS - offset;
					/* (spanning over two cells) */
 			}
 			else /* equal */
 			{
 				y = y2 * CELL_SIZE_PIXELS + offset;
				current_path_height = CELL_SIZE_PIXELS - offset;
					/* (spanning over one cell) */
 			}

 			output << "<rect style='fill:";
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
 		output << " x='0' y='" << offset << "' width='" << PATH_WIDTH;
 		output << "' height='" << PATH_WIDTH << "'/>" << "\n";

 		output << "<rect style='fill:rgb(255,255,255)' ";
 		output << " x='" << (box_width - PATH_WIDTH - offset)  << "' y='";
 		output << (box_height - PATH_WIDTH - offset) << "' width='";
 		output << PATH_WIDTH + offset;
 		output << "' height='" << PATH_WIDTH << "'/>" << "\n";

 		/* footer */
 		output << "</svg>" << "\n";

 		output.close();
 	}
}
