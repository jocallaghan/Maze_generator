#include "astarsolver.h"
#include <iostream>


maze::AStarSolver::AStarSolver(maze::Maze & maze)
{
	this->maze = &maze;
}


/******************************************************************************
* solve_maze() - Computes the pathway of a generated maze. Assumes that
* the maze is correct and that there is a pathway from the start cell to
* the end cell (0,0) and (height - 1, width - 1).
* Updates pathway objects if they are in the solved path.
* A* algorithm (see http://en.wikipedia.org/wiki/A*_search_algorithm)
*****************************************************************************/
void maze::AStarSolver::solve_maze()
{
    std::unordered_set<maze::Cell *> closed_cell_set;

    /* priority queue used to prioritise lower esimated pathway when interating cells
    and mirrored set for fast lookup of membership */
    std::priority_queue<maze::Priority_and_cell> open_cell_p_queue;
    std::unordered_set<maze::Cell *> open_cell_set;

    std::unordered_map<maze::Cell *, maze::Pathway *, std::hash<Cell *> > path_map;

    std::unordered_map<maze::Cell *, unsigned, std::hash<Cell *> > best_known_pathway_number;

    std::unordered_map<maze::Cell *, unsigned, std::hash<Cell *> > estimated_heuristic;

	/* Optimise hash maps */
	unsigned long max_number_pathways = maze->max_num_pathways();
	unsigned long num_cells = maze->num_cells();
	path_map.reserve(max_number_pathways);
	best_known_pathway_number.reserve(num_cells);
	estimated_heuristic.reserve(num_cells);




    maze::Cell * first_cell = maze->get_cell(0, 0);
    maze::Cell * last_cell = maze->get_cell(maze->get_width() - 1, maze->get_height() - 1);

    maze::Cell * current_cell = nullptr;
    maze::Cell * neighbour_cell = nullptr;

    /* Start by pushing the first cell */
    best_known_pathway_number[first_cell] = 0;
    estimated_heuristic[first_cell] = heuristic_estimate(*first_cell);
    open_cell_p_queue.push(Priority_and_cell(first_cell, estimated_heuristic[first_cell]));
    open_cell_set.insert(first_cell);

    while(!open_cell_p_queue.empty())
    {
        Priority_and_cell current_priority_and_cell = open_cell_p_queue.top();
        current_cell = current_priority_and_cell.cell;
        open_cell_p_queue.pop();
        open_cell_set.erase(current_cell);

        if(current_cell == last_cell)
        {
            /* reconstruct */
            maze::SolvingStrategy::build_solved_pathway(&path_map, first_cell, last_cell);
            return;
        }

        closed_cell_set.insert(current_cell);

        /* For each pathway connected to current cell */
        for(maze::Pathway * pathway : *current_cell->get_pathways())
        {
            neighbour_cell = pathway->get_other_cell(current_cell);

            std::unordered_set<maze::Cell *>::const_iterator found_in_closed_set =
                closed_cell_set.find(neighbour_cell);

            if(extra::is_in_container(closed_cell_set, neighbour_cell))
            {
                /* We have already closed this cell; skip to next neighbour */
                continue;
            }

            unsigned tentative_number_pathways = best_known_pathway_number[current_cell] + DISTANCE_BETWEEN_ADJ_CELLS;

            bool neighbour_not_in_open_set = !extra::is_in_container(open_cell_set, neighbour_cell);

            bool known_pathway_exists = extra::is_in_container(best_known_pathway_number, neighbour_cell);

            if(neighbour_not_in_open_set || (known_pathway_exists && tentative_number_pathways < best_known_pathway_number[neighbour_cell]))
            {
                path_map[neighbour_cell] = pathway;
                best_known_pathway_number[neighbour_cell] = tentative_number_pathways;
                estimated_heuristic[neighbour_cell] = best_known_pathway_number[current_cell] + heuristic_estimate(*neighbour_cell);

                if(neighbour_not_in_open_set)
                {
                    open_cell_p_queue.push(Priority_and_cell(neighbour_cell, estimated_heuristic[neighbour_cell]));
                    open_cell_set.insert(neighbour_cell);
                }
            }

        }      


    }

    /* If we reach this point we have encountered an error: we iterated over the open set but didnt find
    the last cell - the maze is not as assumed */

    throw CannotSolveMaze("Maze has errors");  

}

unsigned maze::AStarSolver::heuristic_estimate(maze::Cell & cell)
{
    return maze->get_width() - cell.get_x_position() - 1 +
        maze->get_height() - cell.get_y_position() - 1;
}