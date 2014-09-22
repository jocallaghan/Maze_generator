#include "kruskalgenerator.h"
/*#include <iostream>*/

namespace maze
{
	std::shared_ptr<maze::Maze> maze::KruskalGenerator::make_maze()
	{
		/*  Algorithm: https://en.wikipedia.org/wiki/
        Maze_generation_algorithm#Randomized_Kruskal.27s_algorithm 
        (accessed 21/09/14)
    	*/

    	/* Initialize maze object */
    	std::shared_ptr<maze::Maze> maze(new Maze(height, width));

    	std::mt19937 mt (seed);

    	std::stack<maze::Cell *> path_stack;

        /* First we need a list of pointers to all cells */
        std::vector<std::vector<maze::Cell *> > * all_cells = maze->get_cells();

        /* Now, make a new disjoint-set of these cells */
        josh::Disjoint_set<maze::Cell *> cell_set;

        for(std::vector<maze::Cell *> row : *all_cells)
        {
            for(maze::Cell * cell : row)
            {
                cell_set.add(cell);
                /*std::cerr << "cell[" << cell->get_y_position() << "][" << cell->get_x_position() << "] \n";*/
                /*std::cerr << "Added to cell set: cell[" << cell_set.find_set(cell)->get_object()->get_y_position() << "][" << cell_set.find_set(cell)->get_object()->get_x_position() 
                    << "] pointer: " << cell << "\n";*/
            }
        }

        /* Now we need a list of all possible pathways - To save on redundant checks, 
           we can break the operation into multiple parts */
        std::vector<maze::Pathway *> possible_pathways;

        for(unsigned y = 0; y < height - 1; y++) /* each row except last */
        {
            for (unsigned x = 0; x < width - 1; x++) /* each column except last */
            {
                /* Add a pathway form the current cell to the cell to the right into possible pathways */
                /*std::cerr << "y: " << y << ", x: " << x << "\n";*/
                possible_pathways.push_back(new Pathway(maze->get_cell(x,y), maze->get_cell(x + 1, y)));
               /* std::cerr << "Added pathway: cell[" << maze->get_cell(x,y)->get_y_position() << "][" <<  maze->get_cell(x,y)->get_x_position() << "] to cell["
                    << maze->get_cell(x + 1, y)->get_y_position() << "][" <<  maze->get_cell(x + 1, y)->get_x_position() << "]\n";*/

                /* Add a pathway form the current cell to the cell to the bottom into possible pathways */
                possible_pathways.push_back(new Pathway(maze->get_cell(x,y), maze->get_cell(x, y + 1)));
                /*std::cerr << "Added pathway: cell[" << maze->get_cell(x,y)->get_y_position() << "][" <<  maze->get_cell(x,y)->get_x_position() << "] to cell["
                    << maze->get_cell(x, y + 1)->get_y_position() << "][" <<  maze->get_cell(x, y + 1)->get_x_position() << "]\n";*/

            }
        }

        for(unsigned y = 0; y < height - 1; y++) /* each row except last */
        {
            /* Add a pathway form the end (column) cell to the cell bellow into possible pathways */
            possible_pathways.push_back(new Pathway(maze->get_cell(width - 1, y), maze->get_cell(width - 1, y + 1)));
            /*std::cerr << "Added pathway: cell[" << maze->get_cell(width - 1,y)->get_y_position() << "][" <<  maze->get_cell(width - 1,y)->get_x_position() << "] to cell["
                    << maze->get_cell(width - 1, y + 1)->get_y_position() << "][" <<  maze->get_cell(width - 1, y + 1)->get_x_position() << "]\n";*/
        }

        for(unsigned x = 0; x < width - 1; x++) /* each column except last */
        {
            /* Add a pathway form the end (row) cell to the cell to the right into possible pathways */
            possible_pathways.push_back(new Pathway(maze->get_cell(x, height - 1), maze->get_cell(x + 1, height - 1)));
            /*std::cerr << "Added pathway: cell[" << maze->get_cell(x,height - 1)->get_y_position() << "][" <<  maze->get_cell(x,height - 1)->get_x_position() << "] to cell["
                    << maze->get_cell(x + 1, height - 1)->get_y_position() << "][" <<  maze->get_cell(x + 1, height - 1)->get_x_position() << "]\n";*/
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
                std::cerr << "Could not find cell[" << cell1->get_y_position() << "][" << cell1->get_x_position() << "] pointer: " << cell1 << "\n";
                throw maze::CannotGenerateMaze("Error with maze cell generation");
            }
            /*std::cerr << "found cell[" << cell1->get_y_position() << "][" << cell1->get_x_position() << "] pointer: " << cell1 << "\n";*/
            
            try
            {
                set_of_cell2 = cell_set.find_set(cell2);
            }
            catch (const josh::CannotFindObject)
            {
                std::cerr << "Could not find cell[" << cell2->get_y_position() << "][" << cell2->get_x_position() << "] pointer: " << cell2 << "\n";
                throw maze::CannotGenerateMaze("Error with maze cell generation");
            }
            /*std::cerr << "found cell[" << cell2->get_y_position() << "][" << cell2->get_x_position() << "] pointer: " << cell2 << "\n";*/


            if(cell_set.is_disjoint(set_of_cell1, set_of_cell2))
            {
                /*std::cerr << "Set disjoint: cell[" << cell1->get_y_position() << "][" << cell1->get_x_position() << "] and cell ["
                    << cell1->get_y_position() << "][" << cell1->get_x_position() << "]\n";*/
                /* add pathway to maze */
                maze->add_pathway(random_pathway);

                /* Union the two sets */
                cell_set.union_sets(set_of_cell1, set_of_cell2);

                
            }
            else
            {
                /*std::cerr << "Set not disjoint: cell[" << cell1->get_y_position() << "][" << cell1->get_x_position() << "] and cell ["
                    << cell1->get_y_position() << "][" << cell1->get_x_position() << "]\n";*/

                /* we wont need the allocated pathway */
                delete random_pathway;
            }

            
        }

    	return maze;
	}
}
