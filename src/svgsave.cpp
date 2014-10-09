#include "svgsave.h"

namespace maze
{
	/* Persisit maze to a SVG file. */
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
		unsigned box_width = CELL_SIZE_PIXELS * maze->get_width() + offset;
		unsigned box_height = CELL_SIZE_PIXELS * maze->get_height() + offset;
		output << "<svg width='" << box_width << "' ";
		output << "height='" << box_height << "' ";
		output << "xmlns='http://www.w3.org/2000/svg'>" << "\n";

 		/* box */
		output << "<rect width='" << box_width << "' height='" << box_height;
		output << "' style='fill: black' />" << "\n";

 		/* Edges/pathways */

		std::vector<maze::Pathway *> solved_pathway;
		std::vector<maze::Pathway *> unsolved_pathway;

		/* seperate the pathways so we can make sure the solved is on top */
		for(maze::Pathway * pathway : *maze->get_pathways())
		{
			if(pathway->is_in_solved_pathway())
				solved_pathway.push_back(pathway);
			else
				unsolved_pathway.push_back(pathway);
		}

 		/* Now create the unsolved pathways rectangles */

		for(auto * pathway : unsolved_pathway)
		{
			output_pathway(*pathway, offset, output);
		}

 		/* Now create the solved pathways rectangles */ 
 		for(auto * pathway : solved_pathway)
		{
			output_pathway(*pathway, offset, output);
		}

 		/* Entry and exit paths */
 		bool solved = !solved_pathway.empty();
		output << "<rect style='fill:";
 			if(solved)
 				output << SOLVED_PATHWAY_COLOR;
 			else
 				output << PATHWAY_COLOR;
		output << "' x='0' y='" << offset << "' width='" << PATH_WIDTH;
		output << "' height='" << PATH_WIDTH << "'/>" << "\n";

		output << "<rect style='fill:";
 			if(solved)
 				output << SOLVED_PATHWAY_COLOR;
 			else
 				output << PATHWAY_COLOR;
		output << "' x='" << (box_width - PATH_WIDTH - offset)  << "' y='";
		output << (box_height - PATH_WIDTH - offset) << "' width='";
		output << PATH_WIDTH + offset;
		output << "' height='" << PATH_WIDTH << "'/>" << "\n";

 		/* footer */
		output << "</svg>" << "\n";

		output.close();
	}


	void maze::SVGSave::output_pathway(maze::Pathway & pathway, unsigned offset, std::fstream & output)
	{
		unsigned x;
		unsigned y;
		unsigned current_path_width;
		unsigned current_path_height;

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

 	}
