#include "binaryload.h"

namespace maze
{
	std::shared_ptr<maze::Maze> maze::BinaryLoad::make_maze()
	{
		std::fstream binaryFile(file_path, std::ios::in | std::ios::binary);
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
			unsigned x1, x2, y1, y2;

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
			if (x1 >= maze->get_width() || x2 >= maze->get_width() || y1 >= maze->get_height() || y2 >= maze->get_height())
 			{
 				throw maze::CannotGenerateMaze("Edge out of bounds");
 			}

			/* Add pathway to maze */
			maze->add_pathway(maze->get_cell(x1, y1), maze->get_cell(x2, y2));
 			readEdges++;
 		}
 		binaryFile.close();

 		return maze;
	}
}
