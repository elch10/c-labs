#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace kerimov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const point_t & to) noexcept = 0;
    virtual void move(double dx, double dy) noexcept = 0;
    virtual void scale(double ratio) = 0;
    virtual void rotate(double angle) noexcept = 0;
  };
} //kerimov

#endif // SHAPE_HPP
