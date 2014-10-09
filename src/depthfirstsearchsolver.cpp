#include "depthfirstsearchsolver.h"

maze::DepthFirstSearchSolver::DepthFirstSearchSolver(maze::Maze & maze)
{
   this->maze = &maze;
}


/******************************************************************************
* solve_maze() - Computes the pathway of a generated maze. Assumes that
* the maze is correct and that there is a pathway from the start cell to
* the end cell (0,0) and (height - 1, width - 1).
* Updates pathway objects if they are in the solved path.
* Depth first search
*****************************************************************************/
void maze::DepthFirstSearchSolver::solve_maze()
{
    std::stack<maze::Pathway *> pathway_stack;
    std::stack<maze::Cell *> cell_stack;
	std::unordered_set<maze::Pathway *> pathway_set;

    maze::Cell * current_cell = nullptr;

    bool found_pathway;


	maze::Cell * first_cell = maze->get_entry_cell();
	maze::Cell * last_cell = maze->get_exit_cell();

    if(first_cell == nullptr || last_cell == nullptr)
        throw maze::CannotSolveMaze("not initialised");

    cell_stack.push(first_cell);

    while(true)
    {
        current_cell = cell_stack.top();
        if(current_cell == nullptr)
            throw maze::CannotSolveMaze("could not reach last cell");

        /* Get next unvisited pathway */
        for(maze::Pathway * pathway_ptr : *current_cell->get_pathways())
        {
            found_pathway = false;

            if(pathway_set.find(pathway_ptr) == pathway_set.end())
            {
                /* not in pathways, add and push */
                pathway_set.insert(pathway_ptr);
                pathway_stack.push(pathway_ptr);

                /* add adjacent cell to cell stack */
                cell_stack.push(pathway_ptr->get_other_cell(current_cell));

                found_pathway = true;

                break;
            }
        }

        if(!found_pathway)
        {
            /* No unvisited adjacent cells - if end; break loop, if not; pop stack */
            if(current_cell == last_cell)
                break;
            else
            {
                /*pathway_set.erase(pathway_stack.top());*/
                pathway_stack.pop();
                cell_stack.pop();
            }
        }
    }

    /* Now go through the pathways in our solved stack and mark each one */
    while(pathway_stack.size() > 0)
    {
        pathway_stack.top()->set_solved_pathway();
        pathway_stack.pop();
    }
}