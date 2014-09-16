#include "depthfirstsearchsolver.h"
#include <iostream>

maze::DepthFirstSearchSolver::DepthFirstSearchSolver(maze::Maze & maze)
{
   this->maze = &maze;
}


/******************************************************************************
* solve_maze() - Computes the pathway of a generated maze. Assumes that
* the maze is correct and that there is a pathway from the start cell to
* the end cell (0,0) and (height - 1, width - 1).
* Updates pathway objects if they are in the solved path.
*****************************************************************************/
void maze::DepthFirstSearchSolver::solve_maze()
{
    std::stack<maze::Pathway *> pathway_stack;
    std::stack<maze::Cell *> cell_stack;
	std::unordered_set<maze::Pathway *> pathway_set;

    maze::Cell * current_cell = nullptr;

    bool found_pathway;


    maze::Cell * first_cell = maze->get_cell(0, 0);
    maze::Cell * last_cell = maze->get_cell(maze->get_width() - 1, maze->get_height() - 1);

    if(first_cell == nullptr || last_cell == nullptr)
        throw maze::CannotSolveMaze("not initialised");

    cell_stack.push(first_cell);

    while(true)
    {
        current_cell = cell_stack.top();
        if(current_cell == nullptr)
            throw maze::CannotSolveMaze("could not reach last cell");

        /*std::cerr << "\n=====\ncurrent cell: x: " << current_cell->get_x_position()
            << ", y: " << current_cell->get_y_position() << "\n";*/

        /* Get next unvisited pathway */
        for(maze::Pathway * pathway_ptr : *current_cell->get_pathways())
        {
            found_pathway = false;

            /*if(pathway_ptr == nullptr)
                std::cerr << "NULL\n";
            else
            {
                std::cerr << "found pathway: ";
                std::cerr << "x1: " << pathway_ptr->get_first_cell()->get_x_position() 
                    << ", y1: " << pathway_ptr->get_first_cell()->get_y_position()
                    << ", x2: " << pathway_ptr->get_second_cell()->get_x_position() 
                    << ", y2: " << pathway_ptr->get_second_cell()->get_y_position() << "\n";
            }*/


            std::unordered_set<maze::Pathway *>::const_iterator found_in_pathway_set =
                pathway_set.find(pathway_ptr);

            if(found_in_pathway_set == pathway_set.end())
            {
                /*std::cerr << "NOT IN VISTED SET - adding\n";*/

                /* not in pathways, add and push */
                pathway_set.insert(pathway_ptr);
                pathway_stack.push(pathway_ptr);

                /* add adjacent cell to cell stack */
                if(pathway_ptr->get_first_cell() != current_cell)
                    cell_stack.push(pathway_ptr->get_first_cell());
                else if(pathway_ptr->get_second_cell() != current_cell)
                    cell_stack.push(pathway_ptr->get_second_cell());
                else
                    throw maze::CannotSolveMaze("error with edge");

                found_pathway = true;

                break;
            }
            /*else
            {
                std::cerr << "in visited set - ignoring\n";
            }*/
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