#pragma once

#include "maze.h"
#include "persistencestrategy.h"
#include <fstream>
#include <string>
#include <memory>
#include <iostream>

#define CELL_SIZE_PIXELS 20
#define WALL_SIZE_FACTOR 0.1
#define PATHWAY_COLOR "rgb(255,255,255)"
#define SOLVED_PATHWAY_COLOR "rgb(255,0,0)"

namespace maze
{
	class SVGSave : public PersistenceStrategy
	{
		maze::Maze * maze;
		std::string file_path;

		void output_pathway(maze::Pathway & pathway, unsigned offset, std::fstream & output);

		public:
			SVGSave(maze::Maze & maze, std::string file_path) : maze(&maze), file_path(file_path) {};
			virtual void persist_maze();


			const static unsigned int WALL_WIDTH = (unsigned)((double) WALL_SIZE_FACTOR * CELL_SIZE_PIXELS);
			const static unsigned int PATH_WIDTH = CELL_SIZE_PIXELS - 2 * WALL_WIDTH;
	};
}
