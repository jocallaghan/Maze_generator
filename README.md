Maze generator
==============

Solution by Josh O'Callaghan (s3346764@student.rmit.edu.au)
---------------------------------------------------------


### Description
This program will be able to generate mazes given a seed and height and width.
You may save them into binary or SVG format. Binary files can be loaded into
the program so that it may be converted into an SVG.

The SVG will produce an image with a width of CELL_SIZE_PIXELS (can be changed
in svgsave.h) * input width and a height of the same nature.
The reason I had implemented the program in this way is because specifying the
number of cells as the width and height would result in bad aesthetics, and
possible loss of functionality for larger mazes.

The maze factories available are:
* Depth-first search with backtracking.
* Random Kruskal. 

You can also use the following solving strategies to change the pathway colour in SVG output:
* Depth first search 
* Breadth first search
* A* search

A report discussing the differences in implemented algorithmscan be found in
report.pdf


### Installation
Go to the directory of these source files and call
    'make'

To remove the compiled files, simply call
    'make clean'



### Usage

#### Flags
###### --gr seed height width
Recursive backtrack maze generation.
All arguments must be unsigned integers (or strings represented as).

###### --gk seed height width
Randomised Kruskal maze generation.
All arguments must be unsigned integers (or strings represented as).

###### --lb binary_file
Load a binary file that represents a maze.

###### --pd
Solve maze using a depth first search strategy. 
Won't affect binary output, will change colour of paths in SVG output.

###### --pb
Solve maze using a breadth first search strategy. 
Won't affect binary output, will change colour of paths in SVG output.

###### --pa
Solve maze using a A* search strategy. 
Won't affect binary output, will change colour of paths in SVG output.

###### --sb binary_file
Saves a maze to a binary file

###### --sv svg_file
Saves a maze to a SVG

##### Examples

./maze --g 23411 10 10 --sb output.maze   (generate binary maze file with seed 23411 and h/w: 10/10)

./maze -g 22 5 10 --sv output.svg    (generate SVG maze file with seed 22 and h/w: 5/10)

./maze --lb binary_file.maze --pd --sv output.svg   (binary file to SVG with depth first solve)


You may use the argument flags in any order, but make sure you keep their own arguments
in order (-g seed height width). Using the same flag more than once will result
in the program using the last one.

You must use one input and one output type. Using a solving strategy is optional.



