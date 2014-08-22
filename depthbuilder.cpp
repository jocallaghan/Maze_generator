#include "depthbuilder.h"






void maze::build(maze::Maze * maze, const unsigned long &height,
                const unsigned long &width, const std::string &seed)
{

    /*  Algorithm: https://en.wikipedia.org/wiki/
        Maze_generation_algorithm#Recursive_backtracker 

        Changes:
        Since there is no possibility for the stack to
        be empty and have unvisited cells, I decided
        to remove the "pick random cell" segment.
    */


    /* Convert string - sum ASCII values */
    unsigned long seed_long;

    for(unsigned i = 0; i < seed.length(); i++)
    {
    	seed_long += static_cast<unsigned long>(seed[i]);
    }

    /*std::stringstream stream(seed);
    
    stream >> seed_long;*/

    std::mt19937 mt (seed_long);

    maze::Cell * current_cell, * next_cell;

    std::stack<maze::Cell *> path_stack;

    unsigned long long number_of_total_cells = height * width;
    unsigned long long number_of_visited_cells = 0;


    /* Starting at top left */
    path_stack.push(maze->get_cell(0, 0));
    number_of_visited_cells++;

    while(number_of_visited_cells < number_of_total_cells)
    {
        /*std::cerr << "Visted: " << number_of_visited_cells << "/"; 
        std::cerr << number_of_total_cells << "\n";*/
        current_cell = path_stack.top();
        unsigned long current_y_pos = current_cell->get_y_pos();
        unsigned long current_x_pos = current_cell->get_x_pos();
        /*std::cerr << "Current cell y: " << current_y_pos << ", x: ";
        std::cerr << current_x_pos << "\n";*/
        /* Get unvisited neighbouring cells */
        std::vector<maze::Cell *> unvisited_neighbours;
        /* One above - check because unsigned cant be negative*/
        if(current_y_pos != 0)
        {
            maze::Cell * cell_above = maze->get_cell(current_y_pos - 1, 
            	current_x_pos);
            if(cell_above != NULL)
                if(!cell_above->cell_visited())
                    unvisited_neighbours.push_back(cell_above);
        }
        
        /* One below */
        maze::Cell * cell_below = maze->get_cell(current_y_pos + 1, 
        	current_x_pos);
        if(cell_below != NULL)
            if(!cell_below->cell_visited())
                unvisited_neighbours.push_back(cell_below);

        /* One left - check because unsigned cant be negative*/
        if(current_x_pos != 0)
        {
            maze::Cell * cell_left = maze->get_cell(current_y_pos, 
            	current_x_pos - 1);
            if(cell_left != NULL)
                if(!cell_left->cell_visited())
                    unvisited_neighbours.push_back(cell_left);
        }
        
        /* One right */
        maze::Cell * cell_right = maze->get_cell(current_y_pos, 
        	current_x_pos + 1);
        if(cell_right != NULL)
            if(!cell_right->cell_visited())
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

        maze::Cell& first_cell = *current_cell;
        maze::Cell& second_cell = *next_cell;

        maze->add_edge(first_cell, second_cell);
        path_stack.push(next_cell);
        number_of_visited_cells++;
        
    }
    



}

