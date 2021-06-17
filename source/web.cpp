//  This file is part of My First Evolutionary Algorithm
//  Copyright (C) Tait Weicht, 2021.
//  Released under GNU General Public License v3; see LICENSE

#include "emp/web/web.hpp"
#include "emp/math/stats.hpp"
#include "evo-algo/evolve.hpp"
#include "evo-algo/evoConfig.hpp"

#include "emp/config/command_line.hpp"
#include "emp/config/ArgManager.hpp"
#include "emp/prefab/ConfigPanel.hpp"
#include "emp/web/web.hpp"
#include "emp/web/UrlParams.hpp"

// global variable...
// won't go out of scope and get destroyed
// once main completes
Evolve evolver;

emp::web::Document doc("emp_base");

class EvoAnimator : public emp::web::Animate {
  const double width = 640;
  const double height = 480;
  
  size_t iters;
  double xtick;
  double prev_ave = 0;

  emp::web::Canvas fitCanvas{width, height, "fitCanvas"};

  public:

  EvoAnimator(int iterations) {
    iters = iterations;
    xtick = width / iters;
    auto pop = evolver.GetPopulation();
    prev_ave = height/2 - height * emp::Mean(pop)/8;
  }

  void DoFrame() override {
    evolver.Step();
    auto pop = evolver.GetPopulation();
    size_t cur_gen = evolver.GetGeneration();
    double ave = height/2 - height * emp::Mean(pop)/8;
    fitCanvas.Line((cur_gen - 1) * xtick, prev_ave, cur_gen * xtick, ave);
    prev_ave = ave;

    if(cur_gen >= iters) {
      this->Stop();
      std::cout << "Stopped" << "\n";
    }
  }

  const emp::web::Canvas & GetFitnessCanvas() {
    return fitCanvas;
  }
};

EvoAnimator animator(320);

Config cfg;
emp::prefab::ConfigPanel config_panel(cfg);

int main() {
  doc << "<h1>Average Fitness Graph</h1>";
  auto fitCanvas = animator.GetFitnessCanvas();
  fitCanvas.CSS()
  doc << animator.GetFitnessCanvas();
  animator.Start();
}
