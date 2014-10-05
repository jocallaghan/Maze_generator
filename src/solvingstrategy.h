#pragma once


#include "maze.h"
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace maze
{
	class SolvingStrategy
	{
		public:
			virtual void solve_maze() = 0;
            SolvingStrategy() {};
            ~SolvingStrategy() {};
        protected:
            void build_solved_pathway(std::unordered_map<maze::Cell *, maze::Pathway *, std::hash<maze::Cell *> > * path_map, 
                maze::Cell * first_cell, maze::Cell * last_cell);
	};

    class CannotSolveMaze : public std::runtime_error
    {
        public:
            CannotSolveMaze(const std::string& message)
                : std::runtime_error("Cannot solve maze: " +
                    message) {};
    };
}
