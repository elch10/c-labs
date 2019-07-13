#include "circle.hpp"
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t & center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius < 0.0) {
    throw std::invalid_argument("Radius must be nonnegative");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return { center_, 2 * radius_, 2 * radius_ };
}

void Circle::move(const point_t &to)
{
  center_ = to;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
