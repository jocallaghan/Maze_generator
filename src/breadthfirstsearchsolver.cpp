#include "breadthfirstsearchsolver.h"
#include <iostream>

maze::BreadthFirstSearchSolver::BreadthFirstSearchSolver(maze::Maze & maze)
{
   this->maze = &maze;
}


/******************************************************************************
* solve_maze() - Computes the pathway of a generated maze. Assumes that
* the maze is correct and that there is a pathway from the start cell to
* the end cell (0,0) and (height - 1, width - 1).
* Updates pathway objects if they are in the solved path.
*****************************************************************************/
void maze::BreadthFirstSearchSolver::solve_maze()
{
    /* Set of all visited cells */
    std::unordered_set<maze::Cell *> visited_cells;

    /* Map cell to pathway - used when we need to get correct pathways */
    std::unordered_map<maze::Cell *, maze::Pathway *, std::hash<Cell *> > path_map; 

    /* Cells added by breath first to expand */
    std::queue<maze::Cell *> cells_to_expand;

    maze::Cell * first_cell = maze->get_cell(0, 0);
    maze::Cell * last_cell = maze->get_cell(maze->get_width() - 1, maze->get_height() - 1);

    maze::Cell * current_cell = nullptr;

    /* Start by pushing the first cell to the queue */
    cells_to_expand.push(first_cell);

    
    while(!cells_to_expand.empty())
    {
        current_cell = cells_to_expand.front();
        cells_to_expand.pop();

        if(current_cell == last_cell)
        {
            /* We have reached the last cell, build the solved pathway and stop the search */
            build_solved_pathway(&path_map, first_cell, last_cell);
            break;
        }
        else
        {
            /* Find unvisited neighbouring cells and add to expand queue and visited set */
            for(maze::Pathway * pathway : *(current_cell->get_pathways()))
            {
                maze::Cell * neighbouring_cell = pathway->get_other_cell(current_cell);

                std::unordered_set<maze::Cell *>::const_iterator found_in_visited_set =
                    visited_cells.find(neighbouring_cell);

                if(found_in_visited_set == visited_cells.end())
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

/* Builds the solved pathway. Marks all the pathways in the solved pathway. It does this by 
starting at the given last_cell and then finds the cell with a pathway to it using the path_map.
It does this with the cells it finds until we reach the first_cell */
void maze::BreadthFirstSearchSolver::build_solved_pathway(std::unordered_map<maze::Cell *, maze::Pathway *, std::hash<maze::Cell *> > * path_map, 
    maze::Cell * first_cell, maze::Cell * last_cell)
{
    maze::Cell * current_cell = last_cell;

    while(current_cell != first_cell)
    {
        maze::Pathway * current_pathway = (*path_map)[current_cell];
        current_pathway->set_solved_pathway();
        current_cell = current_pathway->get_other_cell(current_cell);
    }
}