#pragma once

#include <algorithm>

#include "emp/base/vector.hpp"
#include "emp/math/Random.hpp"
#include "emp/math/random_utils.hpp"

#include "fitness.hpp"

double doTournament(
  const emp::vector<double>& population,
  emp::Random& rand,
  const std::size_t tournament_size = 7
) {

    emp::vector<std::size_t> choices = emp::Choose(
		rand,
		population.size(),
		tournament_size
	);

    emp::vector<double> selected;
	for (const std::size_t& x: choices) {
		selected.push_back(population[x]);
	}

	const double winner = *std::max_element(
		std::begin(selected),
		std::end(selected),
		[](const double& a, const double& b) {
			return calcFitness(a) < calcFitness(b);
		}
	);

	return winner;
}