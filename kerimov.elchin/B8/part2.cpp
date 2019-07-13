#include "detail.hpp"

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
#include "Figures.hpp"


void part2(std::istream &in, std::ostream &out)
{

  std::list<std::unique_ptr<Shape>> shape;

  std::transform(std::istream_iterator<Line>(in), std::istream_iterator<Line>(),
    std::back_inserter(shape), readShape);

  out << "Original:" << std::endl;
  std::for_each(shape.begin(), shape.end(),
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));

  out << "Left-Right:" << std::endl;
  shape.sort(std::bind(&Shape::isMoreLeft,
    std::bind(&std::unique_ptr<Shape>::get, std::placeholders::_1),
    std::bind(&std::unique_ptr<Shape>::get, std::placeholders::_2)));

  std::for_each(shape.begin(), shape.end(),
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));

  out << "Right-Left:" << std::endl;
  std::for_each(shape.rbegin(), shape.rend(),
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));


  out << "Top-Bottom:" << std::endl;
  shape.sort(std::bind(&Shape::isUpper,
    std::bind(&std::unique_ptr<Shape>::get, std::placeholders::_1),
    std::bind(&std::unique_ptr<Shape>::get, std::placeholders::_2)));

  std::for_each(shape.begin(), shape.end(),
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));

  out << "Bottom-Top:" << std::endl;
  std::for_each(shape.rbegin(), shape.rend(),
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));
}
