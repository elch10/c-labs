#include <iostream>
#include <stdexcept>
#include <cstring>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try {
    if (argc < 2 || strlen(argv[1]) != 1) {
      throw std::invalid_argument("The arguments must be in the following format:\n"
          "number [args]\n"
          "where number is in range 1-4, args - additional arguments for every number");
    }
    switch(argv[1][0]) {
    case '1': {
      kerimov::task1(argc, argv);
    } break;
    case '2': {
      kerimov::task2(argc, argv);
    } break;
    case '3': {
      kerimov::task3(argc, argv);
    } break;
    case '4': {
      kerimov::task4(argc, argv);  
    } break;
    default: {
      throw std::invalid_argument("The arguments must be in the following format:\n"
          "number [args]\n"
          "where number is in range 1-4, args - additional arguments for every number");
    } break;
    }
  } catch(std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
