#include "detail.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <memory>
#include <sstream>
#include <locale>
#include <list>
#include "Shape.hpp"
#include "Figures.hpp"

bool Line::containNonSpaces()
{
  return std::find_if(begin(), end(),
    [] (char c)
    {
      return !std::isspace(c, std::locale());
    }) != end();
}

std::istream& operator>>(std::istream &input, Line &line)
{
  while (std::getline(input, line)) {
    if (!line.empty() && line.containNonSpaces()) {
      break;
    }
  }
  return input;
}

std::unique_ptr<Shape> readShape(const Line &line)
{
  std::stringstream stream{line};

  std::string type;
  std::getline(stream, type, '(');

  auto firstChar = std::find_if(type.begin(), type.end(),
    std::bind(std::isalpha<char>, std::placeholders::_1, std::locale()));

  type.erase(type.begin(), firstChar); // remove leading whitespaces
  type.erase(std::find_if(firstChar, type.end(),
    std::bind(std::isspace<char>, std::placeholders::_1, std::locale())), type.end()); // and trailing

  double x, y;

  stream >> x;
  stream.ignore(std::numeric_limits<std::streamsize>::max(), ';');

  stream >> y;
  stream.ignore(std::numeric_limits<std::streamsize>::max(), ')');

  if (stream.fail()) {
    throw std::invalid_argument("ERROR: INCORRECT VALUES");
  }

  Line rest;
  std::getline(stream, rest);
  if (rest.containNonSpaces()) {
    throw std::invalid_argument("ERROR: INCORRECT INPUT");
  }

  if(type == "CIRCLE") {
    return std::unique_ptr<Shape>{new Circle{x, y}};
  } else if(type == "TRIANGLE") {
    return std::unique_ptr<Shape>{new Triangle{x, y}};
  } else if(type == "SQUARE") {
    return std::unique_ptr<Shape>{new Square{x, y}};
  } else {
    throw std::invalid_argument("ERROR: INVALID VIGURE NAME");
  }
}
