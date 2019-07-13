#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace kerimov
{
  struct point_t
  {
    double x, y;
    void rotate(double angle) noexcept;
  };

  struct rectangle_t
  {
    point_t pos;
    double width, height;
    bool intersect(const rectangle_t & rhs) noexcept;
  };
}

#endif // BASE_TYPES_HPP
