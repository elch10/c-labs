#include "base-types.hpp"
#include <cmath>

void kerimov::point_t::rotate(double angle) noexcept
{
  double tmpX = x, tmpY = y;
  const double radians = angle * M_PI / 180;
  x = tmpX * cos(radians) - tmpY * sin(radians);
  y = tmpX * sin(radians) + tmpY * cos(radians);
}

bool kerimov::rectangle_t::intersect(const rectangle_t & rhs) noexcept
{
  double lhsLeft = pos.x - width / 2;
  double lhsRight = pos.x + width / 2;
  double lhsDown = pos.y - height / 2;
  double lhsUp = pos.y + height / 2;

  double rhsLeft = rhs.pos.x - rhs.width / 2;
  double rhsRight = rhs.pos.x + rhs.width / 2;
  double rhsDown = rhs.pos.y - rhs.height / 2;
  double rhsUp = rhs.pos.y + rhs.height / 2;

  return !((lhsLeft > rhsRight) || (lhsRight < rhsLeft) || (lhsDown > rhsUp) || (lhsUp < rhsDown));
}
