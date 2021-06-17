#pragma once

#include "emp/config/config.hpp"

EMP_BUILD_CONFIG(Config,
    VALUE(ITERS, double, 320, "Number of iterations"),
    VALUE(POP_SIZE, double, 10, "Population size"),
)

