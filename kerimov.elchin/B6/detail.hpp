#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <iosfwd>
#include <vector>

struct Point
{
  int x, y;
};

typedef std::vector<Point> Shape;

std::istream &operator>>(std::istream &istream, Point &point);
std::istream &operator>>(std::istream &istream, Shape &shape);

std::ostream &operator<<(std::ostream &ostream, const Point &point);
std::ostream &operator<<(std::ostream &ostream, const Shape &shape);

bool isSquare(const Shape& shape);
bool isRectangle(const Shape& shape);

#endif // DETAIL_HPP
