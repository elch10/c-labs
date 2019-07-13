#ifndef FIGURES_HPP
#define FIGURES_HPP

#include "Shape.hpp"
#include <iostream>


class Circle : public Shape
{
public:
  Circle(double x, double y);
  void draw(std::ostream &out) const override;
};

class Triangle : public Shape
{
public:
  Triangle(double x, double y);
  void draw(std::ostream &out) const override;
};

class Square : public Shape
{
public:
  Square(double x, double y);
  void draw(std::ostream &out) const override;
};


#endif // FIGURES_HPP
