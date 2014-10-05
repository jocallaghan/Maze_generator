#include "solvingstrategy.h"

/* Builds the solved pathway. Marks all the pathways in the solved pathway. It does this by 
starting at the given last_cell and then finds the cell with a pathway to it using the path_map.
It does this with the cells it finds until we reach the first_cell */
void maze::SolvingStrategy::build_solved_pathway(std::unordered_map<maze::Cell *, maze::Pathway *, std::hash<maze::Cell *> > * path_map, 
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