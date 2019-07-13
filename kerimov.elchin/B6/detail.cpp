#include "detail.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>

std::istream &operator>>(std::istream &istream, Point &point)
{
  istream.ignore(std::numeric_limits<std::streamsize>::max(), '(');
  istream >> point.x;

  istream.ignore(std::numeric_limits<std::streamsize>::max(), ';');
  istream >> point.y;

  istream.ignore(std::numeric_limits<std::streamsize>::max(), ')');
  return istream;
}

std::istream &operator>>(std::istream &istream, Shape &shape)
{
  shape.clear();

  std::string line;
  
  while (std::getline(istream, line)) // skip lines with only whitespaces
  {
    if (std::find_if(line.begin(), line.end(),
        [] (const char &c)
        {
          return !std::isspace(c, std::locale{});
        }) != line.end()) {
      break;
    }
  }

  if (!istream) {
    return istream;
  }
  
  std::stringstream input(line);
  size_t n;
  input >> n;

  std::copy_n(std::istream_iterator<Point>{input}, n, std::back_inserter(shape));

  if (input.fail() || std::find_if(std::istream_iterator<char>{input}, std::istream_iterator<char>{},
      [] (const char &c)
      {
        return !std::isspace(c, std::locale{});
      }) != std::istream_iterator<char>{}) {
    istream.setstate(std::ios_base::failbit);
  }

  return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Point &point)
{
  return ostream << "(" << point.x << ";" << point.y << ")";
}

std::ostream &operator<<(std::ostream &ostream, const Shape &shape)
{
  ostream << shape.size() << " ";
  std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(ostream, " "));
  return ostream << std::endl;
}

bool isSquare(const Shape& shape)
{
  if (shape.size() != 4) {
    return false;
  }
  if ((shape[1].x != shape[0].x &&
        std::abs(shape[1].x - shape[0].x) != std::abs(shape[2].y - shape[1].y))
      || (shape[1].x == shape[0].x &&
        std::abs(shape[2].x - shape[1].x) != std::abs(shape[1].y - shape[0].y))) {
    return false;
  }
  return true;
}

size_t sqDistance(const Point &a, const Point &b)
{
  return (static_cast<size_t>(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool distancesMakeRightTriangle(const Shape &shape, size_t fromPoint)
{
  size_t distSum = 0, hyp = 0;
  for (size_t i = 0; i < shape.size(); ++i) {
    if (i == fromPoint) {
      continue;
    }
    size_t sqDist = sqDistance(shape[fromPoint], shape[i]);
    distSum += sqDist;
    hyp = std::max(hyp, sqDist);
  }
  if (distSum - hyp == hyp) {
    return true;
  }
  return false;
}

bool isRectangle(const Shape &shape)
{
  if (shape.size() != 4) {
    return false;
  }
  for (size_t i = 0; i < shape.size(); i++) {
    if (!distancesMakeRightTriangle(shape, i)) {
      return false;
    }
  }
  return true;
}

