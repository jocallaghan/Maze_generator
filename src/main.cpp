#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <stdexcept>
#include <climits>
#include <memory>


#include "maze.h"
#include "depthfirstsearchgenerator.h"
#include "kruskalgenerator.h"
#include "binaryload.h"
#include "depthfirstsearchsolver.h"
#include "breadthfirstsearchsolver.h"
#include "astarsolver.h"
#include "binarysave.h"
#include "svgsave.h"
#include "time.h"

const std::string GENERATE_RECURSIVE_FLAG = "--gr";
const std::string GENERATE_KRUSKAL_FLAG = "--gk";
const std::string LOAD_BIN_FLAG = "--lb";	

const std::string SOLVE_DEPTH_FIRST_FLAG = "--pd";
const std::string SOLVE_BREATH_FIRST_FLAG = "--pb";
const std::string SOLVE_A_STAR_FLAG = "--pa";

const std::string SAVE_BIN_FLAG = "--sb"; 
const std::string SAVE_SVG_FLAG = "--sv"; 

void argument_error(std::string program_name);

int main(int argc, char * argv[])
{
	bool generating_recursive = false;
	bool generating_kruskal = false;
	bool loading_binary = false;
	unsigned seed;
	std::string load_path;

	bool saving_binary = false;
	bool saving_svg = false;
	std::string save_path;
	unsigned height, width;

	bool solving_depth_first = false;
	bool solving_breadth_first = false;
	bool solving_a_star = false;

	std::unique_ptr<maze::Maze> maze;
	std::unique_ptr<maze::MazeFactory> factory;
	std::unique_ptr<maze::SolvingStrategy> solving_strategy;
	std::unique_ptr<maze::PersistenceStrategy> persistence_strategy;
	
	std::string program_name = argv[0];
	
	/* Go through the arguments */
	for(int i = 1; i < argc; i++) /* Skip program name */
	{
		std::string current_argument = argv[i];
		std::string next_argument;
		if(i+1 < argc) /* Making sure we have a next argument */
		{
			next_argument = std::string(argv[i+1]);
		}
		else
		{
			next_argument = "";
		}


		if(current_argument == GENERATE_RECURSIVE_FLAG || current_argument == GENERATE_KRUSKAL_FLAG)
		{
			if(current_argument == GENERATE_RECURSIVE_FLAG)
				generating_recursive = true;
			else
				generating_kruskal = true;


			if(next_argument == "") /* No more arguments! */
			{
				std::cerr << "Found generate flag without subsequent data.\n\n";
				argument_error(program_name);
				return 1;
			}
			else
			{
					try
					{
						seed = (unsigned) std::stol(next_argument);
						i += 2; /* we no longer need to read the flag + seed */
					}
					catch (const std::invalid_argument)
					{
						std::cerr << "Seed has to be number.\n\n";
						argument_error(program_name);
						return 1;
					}
					catch (const std::out_of_range)
					{
						std::cerr << "Maximum seed: " << UINT_MAX << ".\n\n";
						argument_error(program_name);
						return 1;
					}
					


					/* Now test for height / width */
					if(i+1 < argc)
					{
						/* There are two more arguments after the seed */
						try 
						{
							height = (unsigned) std::stol(argv[i]); /* fix this */
							width = (unsigned) std::stol(argv[i+1]);
						}
						catch (const std::invalid_argument)
						{
							std::cerr << "Height and/or width have to be ";
							std::cerr << "numbers.\n\n";
							argument_error(program_name);
							return 1;
						}
						catch (const std::out_of_range)
						{
							std::cerr << "Maximum height/width: " << UINT_MAX;
							std::cerr << ".\n\n";
							argument_error(program_name);
							return 1;
						}
						
						i++; /* for loop will skip width also */

					}
					else
					{
						std::cerr << "Found generate flag without height and ";
						std::cerr << "width.\n\n";
						argument_error(program_name);
						return 1;
					}
			}
		}
		else if(current_argument == GENERATE_KRUSKAL_FLAG)
		{
			generating_kruskal = true;
		}
		else if(current_argument == LOAD_BIN_FLAG)
		{
			loading_binary = true;

			if(next_argument == "") /* No more arguments! */
			{
				std::cerr << "Found load flag without subsequent data.\n\n";
				argument_error(program_name);
				return 1;
			}
			else
			{
					load_path = next_argument;
					i++; /* we no longer need to read the argument */
			}
		}
		else if(current_argument == SOLVE_DEPTH_FIRST_FLAG)
		{
			solving_depth_first = true;
		}
		else if(current_argument == SOLVE_BREATH_FIRST_FLAG)
		{
			solving_breadth_first = true;
		}
		else if(current_argument == SOLVE_A_STAR_FLAG)
		{
			solving_a_star = true;
		}
		else if(current_argument == SAVE_BIN_FLAG)
		{
			saving_binary = true;
			if(next_argument == "") /* No more arguments! */
			{
				std::cerr << "Found save bin flag without subsequent data.\n\n";
				argument_error(program_name);
				return 1;
			}
			else
			{
					save_path = next_argument;
					i++; /* we no longer need to read the argument */
			}
		}
		else if(current_argument == SAVE_SVG_FLAG)
		{
			saving_svg = true;
			if(next_argument == "") /* No more arguments! */
			{
				std::cerr << "Found save svg flag without subsequent data.\n\n";
				argument_error(program_name);
				return 1;
			}
			else
			{
					save_path = next_argument;
					i++; /* we no longer need to read the argument */
			}
		}
		else
		{
			/* Found extra info */
			std::cerr << "Ignoring argument \"" << current_argument;
			std::cerr << "\".\n\n";
		}		
		
	}


	/* Now that we have gone through all the arguments, lets see the validity */

	/* Test input flags */
	if(!generating_recursive && !generating_kruskal && !loading_binary)
	{
		std::cerr << "Missing input.\n\n";
		argument_error(program_name);
		return 1;
	}
	else if(
		(generating_recursive && generating_kruskal) ||
		(generating_recursive && loading_binary) ||
		(generating_kruskal && loading_binary)
		)
	{
		std::cerr << "Too many types of input flags.\n\n";
		argument_error(program_name);
		return 1;
	}

	/* Test solving flags */
	if(
		(solving_depth_first && solving_breadth_first) ||
		(solving_depth_first && solving_a_star) ||
		(solving_breadth_first && solving_a_star)
		)
	{
		std::cerr << "Too many types of solving flags.\n\n";
		argument_error(program_name);
		return 1;
	}

	/* Test output flags */
	if(!saving_binary && !saving_svg)
	{
		std::cerr << "Missing output flag.\n\n";
		argument_error(program_name);
		return 1;
	}
	else if(saving_binary && saving_svg)
	{
		std::cerr << "Too many types of output flags.\n\n";
		argument_error(program_name);
		return 1;
	}


	if(saving_binary)
	{
		if(solving_breadth_first || solving_a_star || solving_depth_first)
		{
			std::cerr << "Note that solved pathways wont be saved in binary files.\n";
		}
	}



	/* Now we have our configuration */
	try 
	{

		maze::Time timer;

		if(generating_recursive)
		{
			std::cout << "Generating maze with recursive.\n";
			std::cout << "Height: " << height << ". \n";
			std::cout << "Width: " << width << ". \n";
			std::cout << "Seed: " << seed << ". \n";

			factory = std::unique_ptr<maze::MazeFactory>(new maze::DepthFirstSearchGenerator(height, width, seed));
		}
		else if(generating_kruskal)
		{
			std::cout << "Generating maze with kruskal.\n";
			std::cout << "Height: " << height << ". \n";
			std::cout << "Width: " << width << ". \n";
			std::cout << "Seed: " << seed << ". \n";

			factory = std::unique_ptr<maze::MazeFactory>(new maze::KruskalGenerator(height, width, seed));
		}
		else if(loading_binary)
		{
			std::cout << "Loading maze binary from: " << load_path << ". \n";

			factory = std::unique_ptr<maze::MazeFactory>(new maze::BinaryLoad(load_path));
		}


		timer.milliseconds_since();
		maze = factory->make_maze();
        std::cout << "Generation time: " << timer.milliseconds_since() << " milliseconds. \n";
		

		if(solving_depth_first)
		{
			std::cout << "Solving maze with depth first search.\n";

			solving_strategy = std::unique_ptr<maze::SolvingStrategy>(new maze::DepthFirstSearchSolver(*maze.get()));            
		}
		else if(solving_breadth_first)
		{
			std::cout << "Solving maze with breadth first search.\n";

            solving_strategy = std::unique_ptr<maze::SolvingStrategy>(new maze::BreadthFirstSearchSolver(*maze.get()));            
		}
		else if(solving_a_star)
		{
			std::cout << "Solving maze with A* search.\n";

            solving_strategy = std::unique_ptr<maze::SolvingStrategy>(new maze::AStarSolver(*maze.get()));
		}

		bool solving_maze = solving_depth_first || solving_breadth_first || solving_a_star;

		if(solving_maze)
        {
        	timer.milliseconds_since();
			solving_strategy->solve_maze();
        	std::cout << "Solve time: " << timer.milliseconds_since() << " milliseconds. \n";
        }


		if(saving_binary)
		{
			std::cout << "Saving maze to binary: " << save_path << ". \n";

			persistence_strategy = std::unique_ptr<maze::PersistenceStrategy>(new maze::BinarySave(*maze.get(),save_path));
		}
		else if(saving_svg)
		{
			std::cout << "Saving maze to SVG: " << save_path << ". \n";

			persistence_strategy = std::unique_ptr<maze::PersistenceStrategy>(new maze::SVGSave(*maze.get(),save_path));
		}


        timer.milliseconds_since();
		persistence_strategy->persist_maze();
		std::cout << "Save time: " << timer.milliseconds_since() << " milliseconds. \n";
        

		
	}
	catch (std::runtime_error e)
	{
		std::cerr << e.what() << "\n";
	}
	
} 

void argument_error(std::string program_name)
{
	std::cout << "Incorrect use of arguments. Please use:\n";
	std::cout << program_name << "    <[--gr seed height width] OR \n";
	std::cout << "              [--gk seed height width] OR \n";
	std::cout << "              [--lb filename.maze]> \n";
	std::cout << "          <[--sb filename.maze] OR \n";
	std::cout << "              [--sv filename.svg]>\n";
	std::cout << "          <optional: [--pd] OR [--pb] OR [--pa]>\n";
}