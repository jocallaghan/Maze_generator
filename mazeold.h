#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <algorithm>
#include <stdexcept>



namespace maze 
{

	const short CELL_SIZE_PIXELS = 20;
	const double WALL_SIZE_FACTOR = 0.1;
	

	/* This adds features such as a true border and proper
	   entry & exit points */
	const bool ENHANCED_SVG = true;

	/* Enabling this will add extra paths on an SVG so that the maze has
	   an entry and exit - will only work for enhanced SVG*/
	const bool ENTRY_EXIT_PATHS = true;

	/* Enabling this will solve mazes on default (red path in SVG) */
	const bool SOLVE_MAZE = true;

	/* Don't change */
	const double WALL_WIDTH = CELL_SIZE_PIXELS * WALL_SIZE_FACTOR;
	const double PATH_WIDTH = CELL_SIZE_PIXELS - (2 * WALL_WIDTH);/* 2 sides */

	class CannotGenerateMaze : public std::runtime_error
	{
		public:
			CannotGenerateMaze(const std::string& message)
				: std::runtime_error("Cannot generate maze: " +
					message) {};
	};

	class CannotAddEdge : public std::runtime_error
	{
		public:
			CannotAddEdge(void) 
				: std::runtime_error("Cannot add edge") {};
	};

	typedef struct edge {
		unsigned long x1;
		unsigned long y1;
		unsigned long x2;
		unsigned long y2;
	} Edge;


	class Cell
	{
		
		unsigned long y_pos, x_pos;
		bool path_visited;

		public:
			Cell() : in_solved_path(false) {} 

			std::vector<Cell *> adjacent_cells;
			unsigned long get_y_pos();
			unsigned long get_x_pos();
			void set_y_pos(unsigned long y_pos);	
			void set_x_pos(unsigned long x_pos);

			/* For generation */
			bool cell_visited(); 

			/* For finding the path */
			void set_path_visited();
			bool is_path_visited();

	};


	class Maze {
	private:
		std::vector<Edge> edges;
		Cell ** cells;
		unsigned long height, width;

		std::stack<Cell *> pathway_cells_stack;

	public:
		Maze();

		/* Load pre-generated maze */
		Maze(std::string & file_name);
		
		/* New, empty Maze */	
		Maze(unsigned long height, unsigned long width);

		unsigned long get_width() { return width; }
		unsigned long get_height() { return height; }

		maze::Cell * get_cell(unsigned long y_pos, unsigned long x_pos);
		bool cell_visited(maze::Cell &cell);
		
		void add_edge(maze::Cell &cell1, maze::Cell &cell2);

		void set_pathway(std::stack<Cell *> & pathway_cells);


		/* Saving maze */
		bool save_maze_to_binary(std::string & file_name);
		bool save_maze_to_svg(std::string & file_name);


		~Maze(void);

	};
}
