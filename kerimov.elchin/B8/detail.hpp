#ifndef DETAIL_HPP
#define DETAIL_HPP

#include "parts.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <memory>
#include <sstream>
#include <locale>
#include <list>
#include "Shape.hpp"

class Line : public std::string
{
public:
  bool containNonSpaces();
  friend std::istream &operator>>(std::istream &input, Line &line);
};

std::unique_ptr<Shape> readShape(const Line &line);

#endif // DETAIL_HPP
