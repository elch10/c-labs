#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <iterator>
#include <algorithm>
#include "TextHandler.hpp"

int main(int argc, char ** argv)
{
  if (argc > 3 || argc == 2)
  {
    std::cerr << "Wrong number of arguments!" << std::endl;
    return 1;
  }

  try
  {
    size_t lineWidth = 40;
    if (argc == 3)
    {
      if (strcmp(argv[1], "--line-width"))
      {
        std::cerr << "Need to: --line-width" << std::endl;
        return 1;
      }
      lineWidth = atoi(argv[2]);
      if (lineWidth <= 24)
      {
        std::cerr << "Invalid line-width" << std::endl;
        return 1;
      }
    }

    TextHandler<std::vector<char>::iterator> handler(lineWidth);
    std::vector<char> vector;
    std::cin >> std::noskipws;
    std::copy(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), std::back_inserter(vector));
    if (!std::cin.eof())
    {
      std::cerr << "Read error" << std::endl;
      return 1;
    }

    handler.handle(vector.begin(), vector.end());
  }
  catch (std::invalid_argument & ex)
  {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Other error" << std::endl;
    return 1;
  }

  return 0;
}
