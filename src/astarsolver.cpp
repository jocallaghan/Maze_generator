#include "astarsolver.h"


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

    /* priority queue used to prioritise lower estimated pathway when iterating cells */
    std::priority_queue<maze::Priority_and_cell> open_cell_p_queue;
    /* mirrored set for fast lookup of membership */
    std::unordered_set<maze::Cell *> open_cell_set;
    /* Path map used to find the pathway from the exit back to the entry */
    std::unordered_map<maze::Cell *, maze::Pathway *, std::hash<Cell *> > path_map;
    /* Mappings of statistics and heuristics */
    std::unordered_map<maze::Cell *, unsigned, std::hash<Cell *> > best_known_pathway_number;
    std::unordered_map<maze::Cell *, unsigned, std::hash<Cell *> > estimated_heuristic;

	/* Optimise hash maps */
	unsigned long max_number_pathways = maze->max_num_pathways();
	unsigned long num_cells = maze->num_cells();
	path_map.reserve(max_number_pathways);
	best_known_pathway_number.reserve(num_cells);
	estimated_heuristic.reserve(num_cells);


    maze::Cell * first_cell = maze->get_entry_cell();
    maze::Cell * last_cell = maze->get_exit_cell();

    maze::Cell * current_cell = nullptr;
    maze::Cell * neighbour_cell = nullptr;

    /* Start with the first cell */
    best_known_pathway_number[first_cell] = 0;
    estimated_heuristic[first_cell] = heuristic_estimate(*first_cell);
    open_cell_p_queue.push(Priority_and_cell(first_cell, estimated_heuristic[first_cell]));
    open_cell_set.insert(first_cell);

    /* While we have open cells */
    while(!open_cell_p_queue.empty())
    {
        /* Grab the first cell in the priority queue (and remove from mirrored set) */
        Priority_and_cell current_priority_and_cell = open_cell_p_queue.top();
        current_cell = current_priority_and_cell.cell;
        open_cell_p_queue.pop();
        open_cell_set.erase(current_cell);
        closed_cell_set.insert(current_cell);

        if(current_cell == last_cell)
        {
            /* We have reached the end - reconstruct using path map */
            maze::SolvingStrategy::build_solved_pathway(&path_map, first_cell, last_cell);
            return;
        }

        /* For each pathway connected to current cell */
        for(maze::Pathway * pathway : *current_cell->get_pathways())
        {
            neighbour_cell = pathway->get_other_cell(current_cell);

            if(closed_cell_set.find(neighbour_cell) != closed_cell_set.end())
            {
                /* We have already closed this cell; skip to next neighbour */
                continue;
            }

            unsigned tentative_number_pathways = best_known_pathway_number[current_cell] + DISTANCE_BETWEEN_ADJ_CELLS;
            bool neighbour_not_in_open_set = (open_cell_set.find(neighbour_cell) == open_cell_set.end());
            bool known_pathway_exists = (best_known_pathway_number.find(neighbour_cell) != best_known_pathway_number.end());

            /* If it isn't open or its current statistic can be improved (potential performance boost here:
            since there is always only one pathway with a recursive and kruskal maze, we don't need this) */
            if(neighbour_not_in_open_set || (known_pathway_exists && tentative_number_pathways < best_known_pathway_number[neighbour_cell]))
            {
                /* Add statistic and heuristic */
                path_map[neighbour_cell] = pathway;
                best_known_pathway_number[neighbour_cell] = tentative_number_pathways;
                estimated_heuristic[neighbour_cell] = best_known_pathway_number[current_cell] + heuristic_estimate(*neighbour_cell);

                if(neighbour_not_in_open_set)
                {
                    /* push to open queue (and mirrored set) */
                    open_cell_p_queue.push(Priority_and_cell(neighbour_cell, estimated_heuristic[neighbour_cell]));
                    open_cell_set.insert(neighbour_cell);
                }
            }

        }      


    }

    /* If we reach this point we have encountered an error: we iterated over the open set but didn't find
    the last cell - the maze is not as assumed */

    throw CannotSolveMaze("Maze has errors");  

}

/* This function returns the minimum number pathways between it and
the exit cell */
unsigned maze::AStarSolver::heuristic_estimate(maze::Cell & cell)
{
    return maze->get_width() - cell.get_x_position() - 1 +
        maze->get_height() - cell.get_y_position() - 1;
}