#include "tasks.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
#include <forward_list>
#include "utils.hpp"
#include "sorting.hpp"

/*
  isAscending return true if str equal to "ascending"
  return false if str equal to "ascending"
  generates invalid_argument exception otherwise
*/
bool isAscending(const char *str)
{
  if (!strcmp("ascending", str)) {
    return true;
  } else if (!strcmp("descending", str)) {
    return false;
  } else {
    throw std::invalid_argument(std::string("Error while interpret order:\n") + str
        + " doesn't correspond either `ascending` or `ascending`");
  }
}

void kerimov::task1(int argc, const char *const argv[])
{
  if (argc <= 2) {
    throw std::invalid_argument("Arguments for number=1 must be in the following format:\n"
        "number order\n"
        "where order is `ascending` or `descending` (without quotes)");
  }
  
  bool ascending = isAscending(argv[2]);

  std::vector<int> ints = kerimov::detail::readValues<int>(std::cin);
  
  std::vector<int> copyOfInput = ints;
  kerimov::detail::sort<kerimov::detail::BracketAccess>(copyOfInput, ascending);
  kerimov::detail::printValues(std::cout, copyOfInput, " ", true);

  copyOfInput = ints;
  kerimov::detail::sort<kerimov::detail::AtAccess>(copyOfInput, ascending);
  kerimov::detail::printValues(std::cout, copyOfInput, " ", true);
  
  std::forward_list<int> lst(ints.begin(), ints.end());
  kerimov::detail::sort<kerimov::detail::IteratorAccess>(lst, ascending);
  kerimov::detail::printValues(std::cout, lst, " ", true);
}

void kerimov::task2(int argc, const char *const argv[])
{
  if (argc <= 2) {
    throw std::invalid_argument("Filename as second argument didn't provide."
        "For the number=2 arguments must be in the following format:\n"
        "number filename\n"
        "where filename is name of the file to read from");
  }

  std::ifstream fin(argv[2]);
  if (!fin) {
    throw std::istream::failure(std::string("Can not read file ") + argv[2]);
  }

  const std::streamsize DEFAULT_SIZE = 512;
  const int INCREASING_STRATEGY = 2;

  auto content = std::make_unique< char[] >(DEFAULT_SIZE);
  fin.read(content.get(), DEFAULT_SIZE);
  std::streamsize currentSize = fin.gcount();

  while (!fin.eof()) {
    auto newContent = std::make_unique< char[] >(currentSize * INCREASING_STRATEGY);
    for (std::streamsize sz = 0; sz < currentSize; ++sz) {
      newContent[sz] = content[sz];
    }
    content.swap(newContent);
    fin.read(content.get() + currentSize, (INCREASING_STRATEGY - 1) * currentSize);
    currentSize += fin.gcount();
  }

  std::vector<char> vector(content.get(), content.get() + currentSize);
  kerimov::detail::printValues(std::cout, vector, "", false);
}

void kerimov::task3(int, const char *const[])
{
  using std::cin;

  std::istream::sentry s(cin);
  if (!s && !cin.eof()) {
    throw std::istream::failure("Error while reading: cin is not ready");
  } else if (cin.eof()) { // empty stream
    return;
  }

  std::vector<int> ints;
  int value;

  while (true) {
    cin >> value;
    if (!cin && !cin.eof()) {
      throw std::istream::failure("Error while reading value in stream");
    } else if (cin.eof()) {
      throw std::istream::failure("Error while reading: 0 is not found");
    } else if (value == 0) {
      break;
    }
    ints.push_back(value);
  }
  
  if (ints.empty()) {
    return;
  }

  if (ints.back() == 1) {
    for (auto it = ints.begin(); it != ints.end();) {
      if (*it % 2 == 0) {
        it = ints.erase(it);
      } else {
        ++it;
      }
    }
  } else if (ints.back() == 2) {
    for (auto it = ints.begin(); it != ints.end();) {
      if (*it % 3 == 0) {
        it = ints.insert(it + 1, 3, 1);
        it += 2;
      } else {
        ++it;
      }
    }
  }

  kerimov::detail::printValues(std::cout, ints, " ", true);
}

void kerimov::task4(int argc, const char *const argv[])
{
  if (argc <= 3) {
    throw std::invalid_argument("For number=4 command must take 3 arguments:\n"
        "number order amount\n"
        "where order is `ascending` or `descending` (without quotes)\n"
        "amount is amount of generated values");
  }

  bool ascending = isAscending(argv[2]);

  int size = std::stoi(std::string(argv[3]));

  auto doubles = std::make_unique< double[] >(size);
  kerimov::fillRandom(doubles.get(), size);

  std::cout << std::setprecision(2) << std::fixed;
  std::vector<double> values(doubles.get(), doubles.get() + size);
  kerimov::detail::printValues(std::cout, values, " ", true);

  kerimov::detail::sort<kerimov::detail::BracketAccess>(values, ascending);
  kerimov::detail::printValues(std::cout, values, " " , true);
}
