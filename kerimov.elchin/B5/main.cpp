#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "DataStruct.hpp"

int main()
{
  try {
    std::vector<DataStruct> data;
    std::copy(std::istream_iterator<DataStruct>{std::cin}, std::istream_iterator<DataStruct>{},
      std::back_inserter(data));
    std::sort(data.begin(), data.end());
    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>{std::cout});
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  return 0;
}
