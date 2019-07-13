#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect)
{
  if (rect.width < 0.0 || rect.height < 0.0) {
    throw std::invalid_argument("Height and width must be nonnegative");
  }
}

double Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(const point_t & to)
{
  rect_.pos = to;
}

void Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}
