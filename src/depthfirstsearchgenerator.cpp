#include "depthfirstsearchgenerator.h"
/*#include <iostream>*/

namespace maze
{
    /* Generate a maze using a depthfirst search with recursive backtracking */
    
	std::unique_ptr<maze::Maze> maze::DepthFirstSearchGenerator::make_maze()
	{
		/*  Algorithm: https://en.wikipedia.org/wiki/
        Maze_generation_algorithm#Recursive_backtracker 

        Changes:
        Since there is no possibility for the stack to
        be empty and have unvisited cells, I decided
        to remove the "pick random cell" segment.
    	*/

    	/* Initialize maze object */
    	std::unique_ptr<maze::Maze> maze(new Maze(height, width));

    	std::mt19937 mt (seed);

    	maze::Cell * current_cell = nullptr, * next_cell = nullptr;

        /* The current pathway stack : I didn't use  SolvingStrategy::build_solved_pathway() because it is less
        efficient to store a cell-pathway map which has to be probed and navigated compared
        to the use of a sole pathway stack which is possible with this strategy */
    	std::stack<maze::Cell *> path_stack;

    	unsigned long number_of_total_cells = height * width;
    	unsigned long number_of_visited_cells = 0;

    	/* Starting at top left */
    	path_stack.push(maze->get_cell(0, 0));
    	number_of_visited_cells++;

    	while(number_of_visited_cells < number_of_total_cells)
    	{
        	current_cell = path_stack.top();
        	unsigned current_y_pos = current_cell->get_y_position();
        	unsigned current_x_pos = current_cell->get_x_position();

        	/* Get unvisited neighbouring cells */
        	std::vector<maze::Cell *> unvisited_neighbours;
        	/* One above - check because cant be negative*/
			if (current_y_pos != 0)
        	{
				maze::Cell * cell_above = maze->get_cell(current_x_pos, current_y_pos - 1);
            	if(cell_above != nullptr)
                	if(!cell_above->has_pathway())
                    	unvisited_neighbours.push_back(cell_above);
        	}
        
        	/* One below */

			maze::Cell * cell_below = maze->get_cell(current_x_pos, current_y_pos + 1);
        	if(cell_below != nullptr)
            	if(!cell_below->has_pathway())
                	unvisited_neighbours.push_back(cell_below);
            

        	/* One left - check because unsigned cant be negative*/
			if (current_cell->get_x_position() != 0)
        	{
				maze::Cell * cell_left = maze->get_cell(current_x_pos - 1, current_y_pos);
            	if(cell_left != nullptr)
                	if(!cell_left->has_pathway())
                    	unvisited_neighbours.push_back(cell_left);
        	}
        
        	/* One right */
			maze::Cell * cell_right = maze->get_cell(current_x_pos + 1, current_y_pos);
        	if(cell_right != nullptr)
            	if(!cell_right->has_pathway())
                	unvisited_neighbours.push_back(cell_right);

       		/* Choose path to make with random unvisited neighbours */
        	if(unvisited_neighbours.empty())
        	{
            	/* No more unvisited */
            	path_stack.pop();
            	continue;
        	}

        	/* Randomly select path */
        	unsigned random_index = mt() % unvisited_neighbours.size();
        	/* Decide a path */
        	next_cell = unvisited_neighbours[random_index];

			maze->add_pathway(current_cell, next_cell);
        	path_stack.push(next_cell);
        	number_of_visited_cells++;

            current_cell = nullptr;
        
    	}

    	return maze;
	}
}
