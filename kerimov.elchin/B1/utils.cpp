#include "utils.hpp"
#include <random>

void kerimov::fillRandom(double *array, int size)
{
  std::random_device rnd;
  std::default_random_engine generator(rnd());
  std::uniform_real_distribution<double> distribution(-1, 1);
  for (int i = 0; i < size; ++i) {
    array[i] = distribution(generator);
  }
}
