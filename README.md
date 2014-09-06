Maze generator
==============

Solution by Josh Nithsdale (s3346764@student.rmit.edu.au)
---------------------------------------------------------


### Description
This program will be able to generate mazes given a seed and height and width.
You may save them into binary or SVG format. Binary files can be loaded into
the program so that it may be converted into an SVG.

The SVG will produce an image with a width of CELL_SIZE_PIXELS (can be changed
in maze.h) * input width and a height of the same nature.
The reason I had implemented the program in this way is because specifying the
number of cells as the width and height would result in bad aesthetics, and
possible loss of functionality for larger mazes.
If you wish to use this method of producing SVGs however, you can change 
ENHANCED_SVG in maze.h to false. This method also uses lines instead of
rectangles.
If you used the enhanced SVG, you will have two extra paths for the entry and
exit - this can be disabled by making ENTRY_EXIT_PATHS in maze.h false.

The generator is a depth-first search with backtracking. (see 
https://en.wikipedia.org/wiki/Maze_generation_algorithm#Recursive_backtracker)



### Installation
Go to the directory of these source files and call
    'make'

To remove the compiled files, simply call
    'make clean'



### Usage
./maze -g seed height width --sb output.maze   (generate binary)

./maze -g seed height width --sv output.svg    (generate SVG)

./maze --lb binary_file.maze --sv output.svg   (binary to SVG)


NOTE:
You may use the argument flags in any order, but make sure you keep their args 
in order (-g seed height width). Using the same flag more than once will result
in the program using the last one.



#### Other info
For the maze edges, I used two different structures.
When generating a maze, the most efficient way for me to traverse was to use
a grid of cells, each with an adjacently list with pointers to cells it shares a
path with. It also keeps another extra list of all edges 
(this cell -> other cell).
Although redundant, this extra list is helpful when creating an SVG since we
don't need to keep track of duplicate edges.

When loading a binary file, we only use the list of edges since we don't need 
the grid for traversal.