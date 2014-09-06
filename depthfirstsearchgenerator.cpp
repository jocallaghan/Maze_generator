#include "depthfirstsearchgenerator.h"

namespace maze
{
	std::shared_ptr<maze::Maze> maze::DepthFirstSearchGenerator::make_maze()
	{
		/*  Algorithm: https://en.wikipedia.org/wiki/
        Maze_generation_algorithm#Recursive_backtracker 

        Changes:
        Since there is no possibility for the stack to
        be empty and have unvisited cells, I decided
        to remove the "pick random cell" segment.
    	*/

    	/* Initialize maze object */
    	std::shared_ptr<maze::Maze> maze(new Maze(height, width));

    	/* Convert string - sum ASCII values */
    	unsigned seed_long = 0;

    	for(unsigned i = 0; i < seed.length(); i++)
    	{
    		seed_long += static_cast<unsigned>(seed[i]);
    	}

    	std::mt19937 mt (seed_long);

    	maze::Cell * current_cell, * next_cell;

    	std::stack<maze::Cell *> path_stack;

    	unsigned long number_of_total_cells = height * width;
    	unsigned long number_of_visited_cells = 0;

    	/* Starting at top left */
    	path_stack.push(maze->get_cell(0, 0));
    	number_of_visited_cells++;

    	while(number_of_visited_cells < number_of_total_cells)
    	{
        	current_cell = path_stack.top();
        	unsigned long current_y_pos = current_cell->get_y_position();
        	unsigned long current_x_pos = current_cell->get_x_position();

        	/* Get unvisited neighbouring cells */
        	std::vector<maze::Cell *> unvisited_neighbours;
        	/* One above - check because cant be negative*/
			if (current_cell->get_y_position() != 0)
        	{
				maze::Cell * cell_above = maze->get_cell(current_cell->get_x_position(), current_cell->get_y_position() - 1);
            	if(cell_above != nullptr)
                	if(!cell_above->has_pathway())
                    	unvisited_neighbours.push_back(cell_above);
        	}
        
        	/* One below */
			maze::Cell * cell_below = maze->get_cell(current_cell->get_x_position(), current_cell->get_y_position() + 1);
        	if(cell_below != NULL)
            	if(!cell_below->has_pathway())
                	unvisited_neighbours.push_back(cell_below);

        	/* One left - check because unsigned cant be negative*/
			if (current_cell->get_x_position() != 0)
        	{
				maze::Cell * cell_left = maze->get_cell(current_cell->get_x_position() - 1, current_cell->get_y_position());
            	if(cell_left != NULL)
                	if(!cell_left->has_pathway())
                    	unvisited_neighbours.push_back(cell_left);
        	}
        
        	/* One right */
			maze::Cell * cell_right = maze->get_cell(current_cell->get_x_position() + 1, current_cell->get_y_position());
        	if(cell_right != NULL)
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
        
    	}

    	return maze;
	}
}
