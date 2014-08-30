#include "solve.cpp"

/******************************************************************************
 * compute_path() - Computes the pathway of a generated maze. Assumes that
 * the maze is correct and that there is a pathway from the start cell to
 * the end cell.
 * Updates the pathway_cells_stack in the Maze object which is a stack of cells
 * in order of pathway. The end will be at the top; the start at the bottom.
 *****************************************************************************/
void compute_path(maze::Maze & maze, maze::Cell & start_cell,
	maze::Cell & end_cell)
{
	std::stack<maze::Cell *> path_of_cells;
	maze::Cell * current_cell;
	maze::Cell * adj_cell;

	path_of_cells.push(&start_cell);

	
	while(true)
	{
		current_cell = path_of_cells.top();
		adj_cell = nullptr;

		/* Get next unvisited adjacent cell */
		for(auto cell : current_cell->adjacent_cells)
		{
			if(!cell->is_path_visited())
			{
				adj_cell = cell;
				break;
			}

		}

		if(adj_cell == nullptr)
		{
			/* No unvisited adjacent cells - if end; break loop, if not; pop
			   stack */
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