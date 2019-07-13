#include "Figures.hpp"

Circle::Circle(double x, double y):
  Shape(x, y)
{}

void Circle::draw(std::ostream &out) const
{
  out << "CIRCLE (" << x_ << ";" << y_ << ")" << std::endl;
}

Triangle::Triangle(double x, double y):
  Shape(x, y)
{}

void Triangle::draw(std::ostream &out) const
{
  out << "TRIANGLE (" << x_ << ";" << y_ << ")" << std::endl;
}

Square::Square(double x, double y):
  Shape(x, y)
{}

void Square::draw(std::ostream &out) const
{
  out << "SQUARE (" << x_ << ";" << y_ << ")" << std::endl;
}
