#pragma once

#include "emp/config/config.hpp"

EMP_BUILD_CONFIG(Config,
                 GROUP(MAIN, "Global settings"),
                 VALUE(ITERATIONS, double, 320, "Number of iterations"),
                 VALUE(POPULATION_SIZE, double, 10, "Population size"),
                 VALUE(RECORD_EVERY_NTH, int, 32, "Records every n-th generation in the table (0 gives a default)"))
