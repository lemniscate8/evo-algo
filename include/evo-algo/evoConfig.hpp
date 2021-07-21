#pragma once

#include "emp/config/config.hpp"

EMP_BUILD_CONFIG(Config,
  GROUP(MAIN, "Global settings"),
  VALUE(ITERATIONS, int, 320, "Number of iterations"),
  VALUE(POPULATION_SIZE, double, 750, "Population size"),
  VALUE(RECORD_EVERY_NTH, int, 32, "Records every n-th generation in the table (0 gives a default)"),
//  VALUE(SMALL_INT, int, 5, "Small int"),
//  VALUE(MEDIUM_INT, int, 5, "Medium int"),
//  VALUE(SMALL_FLOAT, float, .1, "Small float"),
//  VALUE(MEDIUM_FLOAT, float, 2, "Medium float"),
//  VALUE(LARGE_INT, int, 1234, "A large value"),
  VALUE(NEGATIVE_FLOAT, float, -.1, "Negative!"),
  VALUE(IS_IT_ON, bool, true, "Exactly what it sounds like..."),
  VALUE(SONNET, std::string, "Shall I compare thee to a summer's day?", "-Shakespeare"),
  GROUP(TEST, "Test another group"),
  VALUE(TEXT, std::string, "Hi \"there", "Some text"),
  VALUE(MORE_TEXT, std::string, "", "Some more text"),
);