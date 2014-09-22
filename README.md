Maze generator
==============

Solution by Josh Nithsdale (s3346764@student.rmit.edu.au)
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

The generator is a depth-first search with backtracking. 

A class diagram can be found in design.svg



### Installation
Go to the directory of these source files and call
    'make'

To remove the compiled files, simply call
    'make clean'



### Usage

#### Flags
###### --gr seed height width
Recursive backtrack maze generation (see https://en.wikipedia.org/wiki/Maze_generation_algorithm#Recursive_backtracker).
All arguments must be unsigned integers (or strings represented as).

###### --gk seed height width
Randomised Kruskal maze generation (see https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_Kruskal.27s_algorithm).
All arguments must be unsigned integers (or strings represented as).

###### --lb binary_file
Load a binary file that represents a maze.

###### --pd
Solve maze using a depth-first search strategy. 
Won't affect binary output, will change color of paths in SVG output.

###### --sb binary_file
Saves a maze to a binary file

###### --sv svg_file
Saves a maze to a SVG

##### Examples

./maze --g 23411 10 10 --sb output.maze   (generate binary maze file with seed 23411 and h/w: 10/10)

./maze -g 22 5 10 --sv output.svg    (generate SVG maze file with seed 22 and h/w: 5/10)

./maze --lb binary_file.maze --pd --sv output.svg   (binary file to SVG with depth first solve)


You may use the argument flags in any order, but make sure you keep their own args 
in order (-g seed height width). Using the same flag more than once will result
in the program using the last one.

You must use one input and one output type. Using a solving strategy is optional.


#### TODO
Add more solving strategies.




##### FIXES NEEDED
* Validate binary files
