#pragma once

#include "squaremaze.h"
#include "persistencestrategy.h"
#include <string>

namespace maze
{
	class SVGSave : public PersistenceStrategy
	{
		maze::SquareMaze * maze;
		std::string file_path;

		public:
			SVGSave(std::shared_ptr<maze::Maze> maze_, std::string file_path_) :
				maze(maze_.get()), file_path(file_path_) {};
			virtual void persist_maze();

			const static unsigned CELL_SIZE_PIXELS = 20;
			constexpr const static char * PATHWAY_COLOR = "rgb(255,255,255)";
			constexpr const static char * SOLVED_PATHWAY_COLOR = "rgb(255,0,0)";
	};
}
