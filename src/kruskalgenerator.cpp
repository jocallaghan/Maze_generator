#include "kruskalgenerator.h"
/*#include <iostream>*/

namespace maze
{
    /* Generate a maze using kruskal */
	std::unique_ptr<maze::Maze> maze::KruskalGenerator::make_maze()
	{
		/*  Algorithm: https://en.wikipedia.org/wiki/
        Maze_generation_algorithm#Randomized_Kruskal.27s_algorithm 
        (accessed 21/09/14)
    	*/

    	/* Initialize maze object */
    	std::unique_ptr<maze::Maze> maze(new Maze(height, width));


        /* List of pointers to all cells */
        std::vector<std::vector<maze::Cell *> > * all_cells = maze->get_cells();
        /* Disjoint-set of these cells */
        josh::Disjoint_set<maze::Cell *> cell_set;
        /* A list of all possible pathways */
        std::vector<maze::Pathway *> possible_pathways;

        std::mt19937 mt (seed);

        /* Fill the disjoint set with the cells */
        for(std::vector<maze::Cell *> row : *all_cells)
        {
            for(maze::Cell * cell : row)
            {
                cell_set.add(cell);
            }
        }

        /* Now we need a list of all possible pathways - To save on redundant checks, 
           we can break the operation into multiple parts */

        /* Main block */
        for(unsigned y = 0; y < height - 1; y++) /* each row except last */
        {
            for (unsigned x = 0; x < width - 1; x++) /* each column except last */
            {
                /* Add a pathway form the current cell to the cell to the right into possible pathways */
                /*std::cerr << "y: " << y << ", x: " << x << "\n";*/
                possible_pathways.push_back(new Pathway(maze->get_cell(x,y), maze->get_cell(x + 1, y)));

                /* Add a pathway form the current cell to the cell to the bottom into possible pathways */
                possible_pathways.push_back(new Pathway(maze->get_cell(x,y), maze->get_cell(x, y + 1)));

            }
        }

        /* Last column */
        for(unsigned y = 0; y < height - 1; y++) /* each row except last */
        {
            /* Add a pathway form the end (column) cell to the cell bellow into possible pathways */
            possible_pathways.push_back(new Pathway(maze->get_cell(width - 1, y), maze->get_cell(width - 1, y + 1)));
        }

        /* Last row */
        for(unsigned x = 0; x < width - 1; x++) /* each column except last */
        {
            /* Add a pathway form the end (row) cell to the cell to the right into possible pathways */
            possible_pathways.push_back(new Pathway(maze->get_cell(x, height - 1), maze->get_cell(x + 1, height - 1)));
        }

        /* Now we can continue with a randomised Kruskal's algorithm
           Since we are using a vector, and we only want to iterate over 
           each pathway only once and at random, the most efficient way
           is to shuffle the list and then traverse */

        std::shuffle(possible_pathways.begin(), possible_pathways.end(), mt);

        for(maze::Pathway * random_pathway : possible_pathways)
        {
            /* See if the cells are disjoint */
            maze::Cell * cell1 = random_pathway->get_first_cell();
            maze::Cell * cell2 = random_pathway->get_second_cell();

            josh::Tree_node<maze::Cell *> * set_of_cell1, * set_of_cell2;

            try 
            {
                set_of_cell1 = cell_set.find_set(cell1);
            }
            catch (const josh::CannotFindObject)
            {
                throw maze::CannotGenerateMaze("Error with maze cell generation");
            }
            
            try
            {
                set_of_cell2 = cell_set.find_set(cell2);
            }
            catch (const josh::CannotFindObject)
            {
                throw maze::CannotGenerateMaze("Error with maze cell generation");
            }


            if(cell_set.is_disjoint(set_of_cell1, set_of_cell2))
            {
                /* They are - add pathway to maze and union two sets */
                maze->add_pathway(random_pathway);
                cell_set.union_sets(set_of_cell1, set_of_cell2);

            }
            else
            {
                /* we wont need the allocated pathway */
                delete random_pathway;
            }

            
        }

    	return maze;
	}
}
