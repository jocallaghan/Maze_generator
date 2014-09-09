#include "depthfirstsearchsolver.h"

DepthFirstSearchSolver(maze::Maze & maze)
{
   this->maze = &maze;
}


/******************************************************************************
* solve_maze() - Computes the pathway of a generated maze. Assumes that
* the maze is correct and that there is a pathway from the start cell to
* the end cell (0,0) and (height - 1, width - 1).
* Updates pathway objects if they are in the solved path.
*****************************************************************************/
void solve_maze()
{
    std::stack<maze::Pathway *> pathway_stack;
    std::stack<maze::Cell *> cell_stack;
    maze::Pathway * current_pathway = nullptr;
    maze::Pathway * adj_pathway = nullptr;
    maze::Cell * current_cell = nullptr;

    bool cell_visited[maze->get_height()][maze->get_width()];

    maze::Cell * first_cell = maze->get_cell(0, 0);
    maze::Cell * last_cell = maze->get_cell(maze->get_height() - 1, maze->get_width() - 1);

    if(first_cell == nullptr || last_cell == nullptr)
        throw maze::CannotSolveMaze("not initialised");

    cell_stack.push_back(first_cell);

    while(true)
    {
        current_cell = cell_stack.top();
        if(current_cell == nullptr)
            throw maze::CannotSolveMaze("could not reach last cell");

        current_pathway = nullptr;
        /* Get next unvisited pathway */
        for(auto pathway_ptr : *current_cell->get_pathways())
        {
            if(!cell->is_path_visited())
            {
                adj_cell = cell;
                break;
            }
        }
        if(adj_cell == nullptr)
        {
            /* No unvisited adjacent cells - if end; break loop, if not; pop stack */
            if(current_cell == &end_cell)
                break;
            else
                path_of_cells.pop();
        }
        else
        {
            /* We have an adjacent cell - push to stack and mark as visited */
            path_of_cells.push(adj_cell)
            adj_cell.set_path_visited();
        }
    }
    maze.set_pathway(path_of_cells);
}