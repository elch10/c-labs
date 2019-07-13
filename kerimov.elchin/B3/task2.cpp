#include <iostream>
#include <ostream>
#include <stdexcept>
#include <list>
#include <iterator>
#include <algorithm>

constexpr int begin = 1;
constexpr int end = 20;
constexpr std::size_t maxSize = 20;

template<class Iterator>
void printValues(Iterator &first, Iterator &last, std::ostream &ostream)
{
  if (first == last) {
    return;
  }
  ostream << *first++;
  if (first == last) {
    ostream << ' ' << *last;
    return;
  }
  ostream << ' ' << *last--;
  if (first != last) {
    ostream << ' ';
    printValues(first, last, ostream);
  }
}

namespace Tasks
{
  void task2(std::istream &istream, std::ostream &ostream)
  {
    std::list<int> list;

    std::transform(std::istream_iterator<int>(istream), std::istream_iterator<int>(),
                   std::insert_iterator<std::list<int>>(list, list.begin()), [](int i)
      {
        if (!(i >= begin && i <= end)) {
          throw std::invalid_argument("number must be >=" + std::to_string(begin) + " && <=" + std::to_string(end));
        }
        return i;
      });

    if (!istream.eof() && (istream.bad() || istream.fail())) {
      throw std::ios_base::failure("Error while reading");
    }
    if (list.empty()) {
      return;
    }
    if (list.size() > maxSize) {
      throw std::out_of_range("Amount of number doesn't satisfy condition of task");
    }

    std::list<int>::iterator begin = list.begin();
    std::list<int>::iterator end = --list.end();
    printValues(begin, end, ostream);

    if (list.size() % 2) {
      if (list.size() != 1) {
        ostream << ' ';
      }
      ostream << *begin;
    }
    ostream << '\n';
  }
}
