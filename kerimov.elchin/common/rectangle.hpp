#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace kerimov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const rectangle_t & rect, double angle = 0);
    virtual double getArea() const noexcept override;
    virtual rectangle_t getFrameRect() const noexcept override;
    virtual void move(const point_t & to) noexcept override;
    virtual void move(double dx, double dy) noexcept override;
    virtual void scale(double ratio) override;
    virtual void rotate(double angle) noexcept override;
  private:
    rectangle_t rect_;
    double angle_;
  };
} //kerimov

#endif // RECTANGLE_HPP
