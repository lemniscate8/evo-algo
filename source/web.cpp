//  This file is part of My First Evolutionary Algorithm
//  Copyright (C) Tait Weicht, 2021.
//  Released under GNU General Public License v3; see LICENSE

#include <emscripten.h>

#include "emp/web/web.hpp"
#include "emp/math/stats.hpp"

#include "evo-algo/evolve.hpp"
#include "evo-algo/evoConfig.hpp"

#include "emp/config/command_line.hpp"
#include "emp/config/ArgManager.hpp"
#include "emp/prefab/ConfigPanel.hpp"
#include "emp/prefab/Card.hpp"
#include "emp/prefab/ValueBox.hpp"
#include "emp/web/UrlParams.hpp"

// global variable...
// won't go out of scope and get destroyed
// once main completes
Evolve evolver;

emp::web::Document doc("emp_base");

Config cfg;

emp::web::Table fitTable(2, 1, "fitTable");

class EvoAnimator : public emp::web::Animate
{
  const double width = 640;
  const double height = 480;
  const int cuttoff = 10;

  size_t iters;
  double xtick;
  double prev_ave = 0;
  int everyN;

  emp::web::Canvas fitCanvas{width, height, "fitCanvas"};

public:
  EvoAnimator(int iterations, int en = 0)
  {
    iters = iterations;
    xtick = width / iters;
    auto pop = evolver.GetPopulation();
    prev_ave = height * (.5 - emp::Mean(pop) / 8);
    everyN = en;
    if (en == 0)
    {
      everyN = iterations / 10;
    }
  }

  void DoFrame() override
  {
    size_t cur_gen = evolver.GetGeneration();
    emp::web::Table table = doc.Table("fitTable");
    size_t columns = table.GetNumCells() / 2;
    if (columns > cuttoff)
    {
      if (columns == cuttoff + 2)
      {
        table.Resize(2, columns + 1);
        table.GetCell(0, columns) << "...";
        table.GetCell(1, columns) << "...";
        table.CellsCSS("border", "1px solid black").CellsCSS("padding", "5px");
        table.Redraw();
      }
    }
    else if (cur_gen % everyN == 0)
    {
      table.Resize(2, columns + 1);
      table.GetCell(0, columns) << cur_gen;
      table.GetCell(1, columns) << prev_ave;
      table.CellsCSS("border", "1px solid black").CellsCSS("padding", "5px");
      table.Redraw();
    }

    evolver.Step();
    auto pop = evolver.GetPopulation();
    double ave = height * (.5 - emp::Mean(pop) / 8);
    fitCanvas.Line((cur_gen - 1) * xtick, prev_ave, cur_gen * xtick, ave);
    prev_ave = ave;

    if (cur_gen >= iters)
    {
      this->Stop();
      std::cout << "Stopped" << "\n";
    }
  }

  const emp::web::Canvas &GetFitnessCanvas()
  {
    return fitCanvas;
  }
};

emp::optional<EvoAnimator> animator;
emp::web::Div canvasHolder;
emp::web::Button startStop([]() {
  std::string label = startStop.GetLabel();
  if(label.compare("Start") == 0) {
    animator->Start();
    startStop.SetLabel("Stop");
  } else {
    animator->Stop();
    startStop.SetLabel("Start");
  }
}, "Start", "startStop");

emp::web::Element resetWithParams("a", "resetWithParams");


int main()
{
  auto specs = emp::ArgManager::make_builtin_specs(&cfg);
  emp::ArgManager am(emp::web::GetUrlParams(), specs);
  am.UseCallbacks();
  if (am.HasUnused())
    std::exit(EXIT_FAILURE);
  cfg["MORE_TEXT"]->SetType("unknown");

  emp::prefab::ConfigPanel config_panel(cfg);
  config_panel.ExcludeSetting("RECORD_EVERY_NTH");
  // config_panel.ExcludeGroup("TEST");
  //config_panel.ExcludeGroup("NONE");
  config_panel.SetRange("ITERATIONS", "DEFAULT", "500");

  config_panel.SetOnChangeFun([](const std::string & name, const std::string & val){
    EM_ASM({
      console.log(UTF8ToString($0));
      console.log(UTF8ToString($1));
    }, name.c_str(), val.c_str());
  });

  animator.emplace(cfg.ITERATIONS(), cfg.RECORD_EVERY_NTH());

  doc << "<h1>Average Fitness Graph</h1>";
  auto fitCanvas = animator->GetFitnessCanvas();
  canvasHolder.SetCSS("border", "2px solid black").SetCSS("width", "min-content");

  doc << config_panel;

  doc << emp::prefab::ValueDisplay("Hi 1", "HI!!!", "Hi there 1");

  // emp::web::Div holder;
  // emp::prefab::ValueDisplay vb1("Hi 1", "HI!!!", "Hi there 1");
  // emp::prefab::ValueDisplay vb2("Hi 2 me hlajfd;lajsdf", "HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII!!!", "Hi there 2");
  // emp::prefab::TextValueControl vb3{
  //   "TC 1", "Text control 1", "initial",
  //   [](std::string val) {
  //     std::cout << val << std::endl;
  //   }
  // };
  // emp::prefab::BoolValueControl vb4{
  //   "BC 1", "Boolean control 1", true,
  //   [](std::string val) {
  //     std::cout << val << std::endl;
  //   }
  // };
  // emp::prefab::NumericValueControl vb5{
  //   "NC 1", "Numeric control 1", "15",
  //   [](std::string val) {
  //     std::cout << val << std::endl;
  //   }
  // };
  // holder << vb1;
  // holder << vb2;
  // holder << vb3;
  // holder << vb4;
  // holder << vb5.Children();

  // holder.SetCSS(
  //   "display", "grid",
  //   "grid-template-columns", "repeat(auto-fill, minmax(300px, 1fr))",
  //   "align-items", "start"
  // );
  // doc << holder;
  emp::vector<emp::web::Div> divVec({emp::web::Div("one"), emp::web::Div("two"), emp::web::Div("three")});
  emp::vector<std::string> stringVec({"hi", "why", "bye"});
  emp::web::Div tester1("tester1");
  emp::web::Div tester2("tester2");
  emp::web::Div tester3("tester3");
  doc << tester1;
  doc << tester2;
  doc << tester3;
  tester1 << divVec;
  tester2 << stringVec;
  tester3 << []() { return "Handles lambdas"; };



  emp::prefab::Card card("INIT_OPEN");
  doc << card;
  card << "Hi there";
  emp::web::Input in([](std::string val){ EM_ASM({ console.log(UTF8ToString($0)) }, val.c_str()); }, "text", "Test");
  card << in;
  //in.Value("hi there\"/> <script> alert(\"hi there\"); </script> <input style='display: none'");

  doc << startStop.AddAttr("class", "btn btn-primary");
  resetWithParams << "Reset";
  doc << resetWithParams.AddAttr("class", "btn btn-danger", "href", "#", "role", "button");
  doc << "<hr>";

  doc << canvasHolder;
  canvasHolder << fitCanvas;
  doc << "<br>";
  doc << fitTable;

  fitTable.GetCell(0, 0) << "Generation";
  fitTable.GetCell(1, 0) << "Average Fitness";
  fitTable.CellsCSS("border", "1px solid black").CellsCSS("padding", "5px");
}
