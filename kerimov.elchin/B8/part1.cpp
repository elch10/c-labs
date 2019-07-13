#define _USE_MATH_DEFINES

#include "parts.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>
#include <cmath>
#include <stdexcept>

void part1(std::istream &in, std::ostream &out)
{
  std::list<double> elemList{std::istream_iterator<double>(in), std::istream_iterator<double>()};

  if (!in.eof()) {
    throw std::iostream::failure("ERROR: INCORRECT INPUT");
  }

  std::transform(elemList.begin(), elemList.end(), elemList.begin(), std::bind2nd(std::multiplies<double>(), M_PI));

  std::copy(elemList.begin(), elemList.end(), std::ostream_iterator<double>(out, " "));
}
