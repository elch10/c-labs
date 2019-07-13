#include "Tasks.hpp"
#include "ContainerOfFactorials.hpp"
#include <iostream>
#include <algorithm>

void Task2()
{
  ContainerOfFactorials container;

  std::copy(container.begin(), container.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}
