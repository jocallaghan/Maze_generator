#pragma once

#include <string>
#include <stack>
#include <random>
#include <sstream>

#include "maze.h"

namespace maze
{
void build(maze::Maze * maze, const unsigned long &height,
				const unsigned long &width, const std::string &seed);



}