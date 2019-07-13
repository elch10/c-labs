#include "Shape.hpp"
#include <ostream>

Shape::Shape(double x, double y):
  x_(x),
  y_(y)
{}

bool Shape::isMoreLeft(const Shape *other) const
{
  return x_< other->x_;
}

bool Shape::isUpper(const Shape *other) const
{
  return y_ > other->y_;
}


