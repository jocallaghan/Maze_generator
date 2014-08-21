#include "maze.h"



/******************************************************************************
 * Maze() - Generates a new clear maze with no edges (paths) given
 * the width and height.
 *****************************************************************************/
 maze::Maze::Maze(unsigned long height, unsigned long width)
 {

	/* Try to alloacte new 2d array of cells */
 	std::cerr << "Generating maze h: " << height << ", w: " << width << "\n";
 	try
 	{
 		this->cells = new Cell*[height];
 	}
 	catch (std::bad_alloc& e)
 	{
 		throw maze::CannotGenerateMaze("Cannot allocate memory");
 	}

 	for(unsigned long count = 0; count < height; count++)
 	{
 		try
 		{
 			this->cells[count] = new Cell[width];
 		}
 		catch (std::bad_alloc& e)
 		{
 			for(unsigned long count2 = 0; count2 < count; count2++)
 			{
 				delete[] this->cells[count2];
 			}
 			throw maze::CannotGenerateMaze("Cannot allocate memory");
 		}
 	}

 	/* Now give each cell its x and y positions */
 	for(unsigned long y_count = 0; y_count < height; y_count++)
 	{
 		for(unsigned long x_count = 0; x_count < width; x_count++)
 		{
 			this->cells[y_count][x_count].set_y_pos(y_count);
 			this->cells[y_count][x_count].set_x_pos(x_count);
 			/*std::cerr << "Assigning x: " << x_count << ", y: " << y_count << "\n";
 			std::cerr << "Found x: " << this->cells[y_count][x_count].get_x_pos() << ", y: " << this->cells[y_count][x_count].get_y_pos() << "\n";*/
 		}
 	}

 	this->height = height;
 	this->width = width;

 }

/******************************************************************************
 * resize_clear_maze() - Replaces maze with a new clear maze with no edges 
 * (paths) given the width and height.
 ****************************************************************************
void maze::Maze::resize_clear_maze(unsigned long height, unsigned long width)
{
	 First test height/width 
	if(height == 0 || width == 0)
	{
		throw CannotGenerateMaze("Height and/or width cannot be less than 1.");
	}

 	this.~Maze();
 	this = Maze(height, width);
}*/

/******************************************************************************
 * get_cell() - Given the y and x coordinates, get the cell of 
 * the maze. Returns NULL if out of bounds.
 *****************************************************************************/
 maze::Cell * maze::Maze::get_cell(unsigned long y_pos, unsigned long x_pos)
 {
 	if(y_pos >= height || x_pos >= width)
 		return NULL;
 	else
 	{
		/*std::cerr << "ask cell y: " << y_pos << ", x: " << x_pos << "\n";
		std::cerr << "got cell y: " << cells[y_pos][x_pos].get_y_pos() << ", x: " << cells[y_pos][x_pos].get_x_pos() << "\n";*/
 		return &this->cells[y_pos][x_pos];
 	}
 }

/******************************************************************************
 * cell_visited() - Check the the given cell has anything in its 
 * adjacent list (visted cell).
 *****************************************************************************/
 bool maze::Maze::cell_visited(maze::Cell &cell)
 {
 	return cell.cell_visited();
 }

 void maze::Maze::add_edge(maze::Cell &cell1, maze::Cell &cell2)
 {
	/* First check if the cells dont already have an edge */

 	if(std::find(cell1.adjacent_cells.begin(), cell1.adjacent_cells.end(),
 		&cell2) != cell1.adjacent_cells.end())
 	{
 		throw maze::CannotAddEdge();
 	}
 	else
 	{
 		cell1.adjacent_cells.push_back(&cell2);
 		cell2.adjacent_cells.push_back(&cell1);

		/* Create edge (for quick saving) */
 		Edge current_edge;

		/* Get data from file */
		/* x1 */
 		current_edge.x1 = cell1.get_x_pos(); 
 		current_edge.y1 = cell1.get_y_pos(); 
 		current_edge.x2 = cell2.get_x_pos(); 
 		current_edge.y2 = cell2.get_y_pos(); 

		/* Add to vector */
 		edges.push_back(current_edge);
 	}
 }


/******************************************************************************
 * ~Maze() - Frees dynamically allocated memory.
 *****************************************************************************/
 maze::Maze::~Maze(void)
 {

 	for(unsigned long count = 0; count < height; count++)
 	{
		/*std::cerr << "Deleting cells y: " << count << "\n";*/
 		delete[] cells[count];
 	}

 	delete[] cells;

 }



/******************************************************************************
 * Maze() - Create a new maze given a path to a binary maze file
 *          !!!!!!!!!NEEDS ERROR CHECKING!!!
 *****************************************************************************/
 maze::Maze::Maze(std::string & file_name)
 {
 	std::fstream binaryFile;
 	unsigned long width = 0, height = 0, numEdges = 0;

 	binaryFile.open(file_name, std::ios::in | std::ios::binary);

 	if(!binaryFile.is_open())
 	{
		/* Error opening file */
 		throw maze::CannotGenerateMaze("Could not open file");
 	}

	/* read header info */
 	binaryFile.read((char*)&width, sizeof(width));
 	binaryFile.read((char*)&height, sizeof(height));
 	binaryFile.read((char*)&numEdges, sizeof(numEdges));

	/* Create Maze */
 	this->height = height;
 	this->width = width;

 	unsigned long readEdges = 0;
	/* edges */
 	while(readEdges < numEdges && !binaryFile.eof())
 	{
		/* Create edge */
 		Edge current_edge;

		/* Get data from file */
		/* x1 */
 		binaryFile.read((char*)&current_edge.x1, sizeof(current_edge.x1));
		/* y1 */
 		binaryFile.read((char*)&current_edge.y1, sizeof(current_edge.y1));
		/* x2 */
 		binaryFile.read((char*)&current_edge.x2, sizeof(current_edge.x2));
		/* y2 */
 		binaryFile.read((char*)&current_edge.y2, sizeof(current_edge.y2));

		/* Add to vector */
 		this->edges.push_back(current_edge);
 		readEdges++;
 	}
 	binaryFile.close();
 }






/******************************************************************************
 * save_maze_to_binary() - save the maze to the given filename as binary
 * (overwrites)
 * return true if successfull.
 *****************************************************************************/
 bool maze::Maze::save_maze_to_binary(std::string & file_name)
 {
 	std::fstream output(file_name,std::fstream::out | std::fstream::binary |
 		std::fstream::trunc);

 	if(!output.is_open())
 	{
		/* Error opening file */
 		fprintf(stderr, "Could not open file for saving binary.\n");
 		return false;
 	}

	/* Write headers */
 	char number_edges = (char) edges.size();
 	output.write((char*)&width, sizeof(width));
 	output.write((char*)&height, sizeof(height));
 	output.write((char*)&number_edges, sizeof(number_edges));

	/* Edges */
 	for(auto & edge : edges)
 	{
		/* x1 */
 		output.write((char*)&edge.x1, sizeof(edge.x1));
		/* y1 */
 		output.write((char*)&edge.y1, sizeof(edge.y1));
		/* x2 */
 		output.write((char*)&edge.x2, sizeof(edge.x2));
		/* y2 */
 		output.write((char*)&edge.y2, sizeof(edge.y2));
 	}
 	output.close();

 	return true;
 }

/******************************************************************************
 * save_maze_to_svg() - save the maze to the given filename as svg (overwrites)
 * return true if successfull.
 *****************************************************************************/
 bool maze::Maze::save_maze_to_svg(std::string & file_name)
 {
 	std::fstream output(file_name,std::fstream::out | std::fstream::trunc);

 	if(!output.is_open())
 	{
		/* Error opening file */
 		fprintf(stderr, "Could not open file for saving svg.\n");
 		return false;
 	}

 	if(ENHANCED_SVG == true)
 	{
 		/* header */
 		unsigned long box_width = CELL_SIZE_PIXELS * width;
 		unsigned long box_height = CELL_SIZE_PIXELS * height;
 		output << "<svg  width='" << box_width << "' ";  /*viewBox='0 0 1 1'*/
 		output << "height='" << box_height << "' ";
 		output << "xmlns='http://www.w3.org/2000/svg'>" << "\n";

 		/* box */
 		output << "<rect width='" << box_width << "' height='" << box_height << "' style='fill: black' />" << "\n";

 		/* Edges */
 		for(auto & edge : edges)
 		{
 			unsigned long x;
 			unsigned long y;
 			unsigned long current_path_width;
 			unsigned long current_path_height;

 			/* Dimentions depends on the edges - some are 
 			   in reverse order (right to left etc) */
 			if(edge.x1 < edge.x2)
 			{
 				x = edge.x1 * CELL_SIZE_PIXELS + WALL_WIDTH;
 				current_path_width = (edge.x2 - edge.x1 + 1) * CELL_SIZE_PIXELS - (2 * WALL_WIDTH);
 			}
 			else
 			{
 				x = edge.x2 * CELL_SIZE_PIXELS + WALL_WIDTH;
 				current_path_width = (edge.x1 - edge.x2 + 1) * CELL_SIZE_PIXELS - (2 * WALL_WIDTH);
 			}

 			if(edge.y1 < edge.y2)
 			{
 				y = edge.y1 * CELL_SIZE_PIXELS + WALL_WIDTH;
 				current_path_height = (edge.y2 - edge.y1 + 1) * CELL_SIZE_PIXELS - (2 * WALL_WIDTH);
 			}
 			else
 			{
 				y = edge.y2 * CELL_SIZE_PIXELS + WALL_WIDTH;
 				current_path_height = (edge.y1 - edge.y2 + 1) * CELL_SIZE_PIXELS - (2 * WALL_WIDTH);
 			}

 			output << "<rect style='fill:rgb(255,255,255)' ";
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
 		output << " x='" << (box_width - PATH_WIDTH)  << "' y='" << (box_height - PATH_WIDTH - WALL_WIDTH) << "' width='" << PATH_WIDTH;
 		output << "' height='" << PATH_WIDTH << "'/>" << "\n";

 	}
 	else
 	{
 		/* header */
 		output << "<svg viewBox='0 0 1 1' width='500' height='500' ";
 		output << "xmlns='http://www.w3.org/2000/svg'>" << "\n";
 		output << "<rect width='1' height='1' style='fill: black' />" << "\n";

		/* Edges */
 		for(auto & edge : edges)
 		{
 			output << "<line stroke='white' stroke-width='0.005' x1='";
 			output << (double) edge.x1 / width  << "' y1='";
 			output << (double) edge.y1 / height << "' x2='";
 			output << (double) edge.x2 / width << "' y2='";
 			output << (double) edge.y2 / height << "'/>" << "\n";
 		}
 	}


	/* footer */
 	output << "</svg>" << "\n";


 	output.close();

 	return true;
 }



 unsigned long maze::Cell::get_y_pos()
 {
 	return y_pos;
 }

 unsigned long maze::Cell::get_x_pos()
 {
 	return x_pos;
 }

 void maze::Cell::set_y_pos(unsigned long y_pos)
 {
 	this->y_pos = y_pos;
 }

 void maze::Cell::set_x_pos(unsigned long x_pos)
 {
 	this->x_pos = x_pos;
 }

/******************************************************************************
 * cell_visited() - Check the the given cell has anything in its 
 * adjacent list (visted cell).
 *****************************************************************************/
 bool maze::Cell::cell_visited(void)
 {
 	return !this->adjacent_cells.empty();
 }

/******************************************************************************
 * ~Cell() - Frees cell
 *****************************************************************************/
 maze::Cell::~Cell(void)
 {

 }


