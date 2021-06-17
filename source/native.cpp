//  This file is part of My First Evolutionary Algorithm
//  Copyright (C) Tait Weicht, 2021.
//  Released under GNU General Public License v3; see LICENSE

#include <iostream>

#include "emp/base/vector.hpp"
#include "emp/config/command_line.hpp"

#include "evo-algo/evolve.hpp"

// This is the main function for the NATIVE version of My First Evolutionary Algorithm.

int main(int argc, char* argv[])
{
  emp::vector<std::string> args = emp::cl::args_to_strings(argc, argv);

  std::cout << "Hello, world!" << std::endl;

  std::cout << "evolved, yo!" << '\n';

  return 0;
}
