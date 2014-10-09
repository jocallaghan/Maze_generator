#include "breadthfirstsearchsolver.h"

maze::BreadthFirstSearchSolver::BreadthFirstSearchSolver(maze::Maze & maze)
{
   this->maze = &maze;
}


/******************************************************************************
* solve_maze() - Computes the pathway of a generated maze. Assumes that
* the maze is correct and that there is a pathway from the start cell to
* the end cell (0,0) and (height - 1, width - 1).
* Updates pathway objects if they are in the solved path.
* Breadth first search.
*****************************************************************************/
void maze::BreadthFirstSearchSolver::solve_maze()
{
    /* Set of all visited cells */
    std::unordered_set<maze::Cell *> visited_cells;
    /* Map cell to pathway - used when we need to get correct pathways */
    std::unordered_map<maze::Cell *, maze::Pathway *, std::hash<Cell *> > path_map; 
    /* Cells added by breath first to expand */
    std::queue<maze::Cell *> cells_to_expand;

    /* Optimise hash map */
    path_map.reserve(maze->max_num_pathways());

    maze::Cell * first_cell = maze->get_entry_cell();
    maze::Cell * last_cell = maze->get_exit_cell();

    maze::Cell * current_cell = nullptr;
    maze::Cell * neighbouring_cell = nullptr;

    /* Start by pushing the first cell to the queue */
    cells_to_expand.push(first_cell);

    /* While we have cells to expand */
    while(!cells_to_expand.empty())
    {
        /* grab the first */
        current_cell = cells_to_expand.front();
        cells_to_expand.pop();

        if(current_cell == last_cell)
        {
            /* We have reached the last cell, build the solved pathway and stop the search */
            maze::SolvingStrategy::build_solved_pathway(&path_map, first_cell, last_cell);
            break;
        }
        else
        {
            /* Find unvisited neighbouring cells and add to expand queue and visited set */
            for(maze::Pathway * pathway : *(current_cell->get_pathways()))
            {
                neighbouring_cell = pathway->get_other_cell(current_cell);

                if(visited_cells.find(neighbouring_cell) == visited_cells.end())
                {
                    /* Not yet visited - add to queue, visited cells and pathway map */
                    cells_to_expand.push(neighbouring_cell);
                    visited_cells.insert(neighbouring_cell);
                    path_map[neighbouring_cell] = pathway;
                }

            }
        }
    }

}
