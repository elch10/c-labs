#include "parts.hpp"
#include <algorithm>
#include <numeric>
#include <iterator>

#include "detail.hpp"

void part2(std::istream &in, std::ostream &out)
{
  std::vector<Shape> shapes{std::istream_iterator<Shape>{in}, std::istream_iterator<Shape>{}};

  if (!in.eof()) {
    throw std::istream::failure{"Wrong format of input"};
  }

  size_t totalVertices = std::accumulate(shapes.begin(), shapes.end(), 0ull,
    [] (size_t sum, const Shape &sh)
    {
      return sum + sh.size();
    });
  out << "Vertices: " << totalVertices << std::endl;

  size_t triangles = std::count_if(shapes.begin(), shapes.end(),
    [] (const Shape &sh)
    {
      return sh.size() == 3;
    });
  out << "Triangles: " << triangles << std::endl;

  size_t squares = std::count_if(shapes.begin(), shapes.end(), isSquare);
  out << "Squares: " << squares << std::endl;

  size_t rectangles = std::count_if(shapes.begin(), shapes.end(), isRectangle);
  out << "Rectangles: " << rectangles << std::endl;

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(),
    [] (const Shape &sh)
    {
      return sh.size() == 5;
    }), shapes.end());

  std::vector<Point> points;
  std::transform(shapes.begin(), shapes.end(), std::back_inserter(points),
    [] (const Shape &sh)
    {
      return sh.front();
    });
  out << "Points:";

  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>{out});

  auto triangleEnd = std::partition(shapes.begin(), shapes.end(),
    [] (const Shape &sh)
    {
      return sh.size() == 3;
    });
  
  auto squareEnd = std::partition(triangleEnd, shapes.end(), isSquare);
  
  std::partition(squareEnd, shapes.end(), isRectangle);

  out << "\nShapes:" << std::endl;
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>{out});
}
