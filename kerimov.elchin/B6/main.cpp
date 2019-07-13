#include <iostream>
#include <string>
#include "parts.hpp"

int main(int argc, char *argv[])
{
  if(argc != 2) {
    std::cerr << "Enter the task number [1-2]";
    return 1;
  }

  try {
    int variant = std::stoi(argv[1]);
    switch(variant) {
    case 1:
      part1(std::cin, std::cout);
      break;
    case 2:
      part2(std::cin, std::cout);
      break;
    default:
      std::cerr << "The wrong task number [1-2]" << std::endl;
      return 1;
    }
  } catch(const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
