#include "pathway.h"

/* given a cell, return the other cell in the pathway */
maze::Cell * maze::Pathway::get_other_cell(maze::Cell * cell)
{
    if(cell == this->get_first_cell())
        return this->get_second_cell();
    else if(cell == this->get_second_cell())
        return this->get_first_cell();
    else
        return nullptr;
}

