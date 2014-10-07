#include "binaryload.h"
#include <string>

namespace maze
{
	std::shared_ptr<maze::Maze> maze::BinaryLoad::make_maze()
	{
		std::fstream binaryFile(file_path, std::fstream::in | std::fstream::binary);

 		unsigned width = 0, height = 0, numEdges = 0;


 		if(!binaryFile.is_open())
 		{
			/* Error opening file */
 			throw maze::CannotGenerateMaze("Could not open file");
 		}

		

		/* read header info */
 		binaryFile.read((char*)&width, sizeof(width));
 		binaryFile.read((char*)&height, sizeof(height));
 		binaryFile.read((char*)&numEdges, sizeof(numEdges));

 		/* Test header info */
 		if(width == 0)
 		{
 			throw maze::CannotGenerateMaze("Width cannot be less than 1");
 		}
 		if(height == 0)
 		{
 			throw maze::CannotGenerateMaze("Height cannot be less than 1");
 		}

		/* Initialize maze object */
		std::shared_ptr<maze::Maze> maze(new Maze(height, width));


 		unsigned long readEdges = 0;
		/* edges */
 		while(readEdges < numEdges && !binaryFile.eof())
 		{
			unsigned x1 = 0, x2 = 0, y1 = 0, y2 = 0;

			/* Get data from file */
			/* x1 */
 			binaryFile.read((char*)&x1, sizeof(x1));
			/* y1 */
 			binaryFile.read((char*)&y1, sizeof(y1));
			/* x2 */
 			binaryFile.read((char*)&x2, sizeof(x2));
			/* y2 */
 			binaryFile.read((char*)&y2, sizeof(y2));

 			/* Test data */
 			std::string message;

 			if(x1 >= maze->get_width())
 			{
 				message = "Edge out of bounds: x1: " + std::to_string(x1);
 				
 			}
 			else if(x2 >= maze->get_width())
 			{
 				message = "\nEdge out of bounds: x2: " + std::to_string(x2);
 			}
 			else if(y1 >= maze->get_height())
 			{
 				message = "\nEdge out of bounds: y1: " + std::to_string(y1);
 			}
 			else if(y2 >= maze->get_height())
 			{
 				message = "\nEdge out of bounds: y2: " + std::to_string(y2);
 			}

 			if(message != "")
 				throw maze::CannotGenerateMaze(message);


			/* Add pathway to maze */
			maze->add_pathway(maze->get_cell(x1, y1), maze->get_cell(x2, y2));
 			readEdges++;
 		}
 		binaryFile.close();

		if (readEdges < numEdges)
			throw maze::CannotGenerateMaze("Missing edges");

 		return maze;
	}
}
