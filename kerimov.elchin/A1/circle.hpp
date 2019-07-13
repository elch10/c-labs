#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t & center, double radius);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t & to) override;
  virtual void move(double dx, double dy) override;
private:
  point_t center_;
  double radius_;
};

#endif // CIRCLE_HPP
