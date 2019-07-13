#include "circle.hpp"
#include <cmath>
#include <stdexcept>

kerimov::Circle::Circle(const point_t & center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius < 0.0) {
    throw std::invalid_argument("Radius must be nonnegative");
  }
}

double kerimov::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

kerimov::rectangle_t kerimov::Circle::getFrameRect() const noexcept
{
  return { center_, 2 * radius_, 2 * radius_ };
}

void kerimov::Circle::move(const point_t & to) noexcept
{
  center_ = to;
}

void kerimov::Circle::move(double dx, double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}

void kerimov::Circle::scale(double ratio)
{
  if (ratio < 0.0) {
    throw std::invalid_argument("Ratio must be non-negative");
  }
  radius_ *= ratio;
}

void kerimov::Circle::rotate(double) noexcept
{}
