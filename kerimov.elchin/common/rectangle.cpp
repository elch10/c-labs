#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>

kerimov::Rectangle::Rectangle(const rectangle_t & rect, double angle):
  rect_(rect),
  angle_(angle)
{
  if (rect.width < 0.0 || rect.height < 0.0) {
    throw std::invalid_argument("Height and width must be nonnegative");
  }
}

double kerimov::Rectangle::getArea() const noexcept
{
  return rect_.width * rect_.height;
}

kerimov::rectangle_t kerimov::Rectangle::getFrameRect() const noexcept
{ 
  point_t leftUp = {-rect_.width / 2, rect_.height / 2};
  point_t leftDown = {-rect_.width / 2,-rect_.height / 2};
  point_t rightUp = {rect_.width / 2, rect_.height / 2};
  point_t rightDown = {rect_.width / 2, -rect_.height / 2};

  leftUp.rotate(angle_);
  leftDown.rotate(angle_);
  rightUp.rotate(angle_);
  rightDown.rotate(angle_);
  
  double left = std::min(std::min(leftUp.x, leftDown.x), std::min(rightUp.x, rightDown.x));
  double right = std::max(std::max(leftUp.x, leftDown.x), std::max(rightUp.x, rightDown.x));
  double down = std::min(std::min(leftUp.y, leftDown.y), std::min(rightUp.y, rightDown.y));
  double up = std::max(std::max(leftUp.y, leftDown.y), std::max(rightUp.y, rightDown.y));

  return { rect_.pos, right - left, up - down };
}

void kerimov::Rectangle::move(const point_t & to) noexcept
{
  rect_.pos = to;
}

void kerimov::Rectangle::move(double dx, double dy) noexcept
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void kerimov::Rectangle::scale(double ratio)
{
  if (ratio < 0.0) {
    throw std::invalid_argument("Ratio must be non-negative");
  }
  rect_.height *= ratio;
  rect_.width *= ratio;
}

void kerimov::Rectangle::rotate(double angle) noexcept
{
  angle_ = std::fmod(angle_ + angle, 360.0);
}
