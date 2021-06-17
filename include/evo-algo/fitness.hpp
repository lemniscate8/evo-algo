#pragma once

#include <cmath>

double calcFitness(const double x) {
	return std::sin(2 * x) + std::sin(6.0 * x) + std::sin(10.0 * x) - std::cos(x);
}