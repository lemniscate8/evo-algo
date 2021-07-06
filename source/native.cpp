//  This file is part of My First Evolutionary Algorithm
//  Copyright (C) Tait Weicht, 2021.
//  Released under GNU General Public License v3; see LICENSE

#include <iostream>

#include "emp/base/vector.hpp"
#include "emp/config/command_line.hpp"
#include "emp/config/ArgManager.hpp"
#include "emp/prefab/ConfigPanel.hpp"

#include "evo-algo/evolve.hpp"
#include "evo-algo/evoConfig.hpp"

// This is the main function for the NATIVE version of My First Evolutionary Algorithm.

Config cfg;

int main(int argc, char* argv[])
{
  auto specs = emp::ArgManager::make_builtin_specs(&cfg);
  emp::ArgManager am(argc, argv, specs);
  am.UseCallbacks();
  if (am.HasUnused())
    std::exit(EXIT_FAILURE);
  cfg.Write(std::cout);
  for(int i = 0; i < argc; i++) {
    std::cout << argv[i] << std::endl;
  }

  std::cout << "Hello, world!" << std::endl;

  std::cout << "evolved, yo!" << '\n';

  return 0;
}
