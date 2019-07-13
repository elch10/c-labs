#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace kerimov
{
  class Circle: public Shape
  {
  public:
    Circle(const point_t & center, double radius);
    virtual double getArea() const noexcept override;
    virtual rectangle_t getFrameRect() const noexcept override;
    virtual void move(const point_t & to) noexcept override;
    virtual void move(double dx, double dy) noexcept override;
    virtual void scale(double ratio) override;
    virtual void rotate(double angle) noexcept override;
  private:
    point_t center_;
    double radius_;
  };
} //kerimov

#endif // CIRCLE_HPP
