#include "parts.hpp"
#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_set>

void part1(std::istream &in, std::ostream &out)
{
  std::unordered_set<std::string> uniqueWords;
  std::copy(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>(),
      std::inserter(uniqueWords, uniqueWords.begin()));

  std::copy(uniqueWords.begin(), uniqueWords.end(), std::ostream_iterator<std::string>(out, "\n"));
}
