#include "composite-shape.hpp"
#include <algorithm>
#include <numeric>
#include <stdexcept>

kerimov::CompositeShape::CompositeShape() noexcept:
  shapes_(),
  size_(0)
{}

kerimov::CompositeShape::CompositeShape(const kerimov::CompositeShape & rhs):
  shapes_(std::make_unique< element_type[] >(rhs.size_)),
  size_(rhs.size_)
{
  std::copy(rhs.shapes_.get(), rhs.shapes_.get() + size_, shapes_.get());
}

kerimov::CompositeShape::CompositeShape(kerimov::CompositeShape && rhs) noexcept:
  shapes_(std::move(rhs.shapes_)),
  size_(rhs.size_)
{
  rhs.size_ = 0;
}

kerimov::CompositeShape & kerimov::CompositeShape::operator= (const kerimov::CompositeShape & rhs)
{
  if (this == &rhs) {
    return *this;
  }
  shapes_ = std::make_unique< element_type[] >(rhs.size_);
  size_ = rhs.size_;
  std::copy(rhs.shapes_.get(), rhs.shapes_.get() + size_, shapes_.get());
  return *this;
}

kerimov::CompositeShape & kerimov::CompositeShape::operator= (kerimov::CompositeShape && rhs) noexcept
{
  shapes_ = std::move(rhs.shapes_);
  size_ = rhs.size_;
  rhs.size_ = 0;
  return *this;
}

kerimov::CompositeShape::element_type & kerimov::CompositeShape::operator[] (size_t index) const
{
  validateIndex(index);
  return shapes_[index];
}

double kerimov::CompositeShape::getArea() const noexcept
{
  return std::accumulate(shapes_.get(), shapes_.get() + size_, 0.0,
    [] (double sum, const element_type & shape) {
      return sum + shape->getArea();
  });
}

kerimov::rectangle_t kerimov::CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0) {
    return {0.0, 0.0, 0.0, 0.0};
  }
  rectangle_t rect = shapes_[0]->getFrameRect();
  double left = rect.pos.x - rect.width / 2;
  double right = rect.pos.x + rect.width / 2;
  double up = rect.pos.y + rect.height / 2;
  double down = rect.pos.y - rect.height / 2;

  for_each(shapes_.get() + 1, shapes_.get() + size_, [&] (const element_type & element) {
    rect = element->getFrameRect();
    left = std::min(left, rect.pos.x - rect.width / 2);
    right = std::max(right, rect.pos.x + rect.width / 2);
    down = std::min(down, rect.pos.y - rect.height / 2);
    up = std::max(up, rect.pos.y + rect.height / 2);
  });

  return { {left + (right - left) / 2, down + (up - down) / 2}, right - left, up - down };
}

void kerimov::CompositeShape::move(const point_t & to) noexcept
{
  point_t center = getFrameRect().pos;
  move(to.x - center.x, to.y - center.y);
}

void kerimov::CompositeShape::move(double dx, double dy) noexcept
{
  for_each(shapes_.get(), shapes_.get() + size_, [dx, dy] (element_type & shape) {
    shape->move(dx, dy);
  });
}

void kerimov::CompositeShape::scale(double ratio)
{
  if (ratio < 0.0) {
    throw std::invalid_argument("Ratio must be non-negative");
  }
  point_t compositeCenter = getFrameRect().pos;
  for_each(shapes_.get(), shapes_.get() + size_, [&compositeCenter, ratio] (element_type & element) {
    point_t elementCenter = element->getFrameRect().pos;
    element->move((elementCenter.x - compositeCenter.x) * (ratio - 1),
        (elementCenter.y - compositeCenter.y) * (ratio - 1));
    element->scale(ratio);
  });
}

void kerimov::CompositeShape::rotate(double angle) noexcept
{
  point_t compositeCenter = getFrameRect().pos;

  for_each(shapes_.get(), shapes_.get() + size_, 
    [&compositeCenter, angle] (element_type & shape) {
      point_t elementVector = shape->getFrameRect().pos;
      elementVector = { elementVector.x - compositeCenter.x, elementVector.y - compositeCenter.y };
      elementVector.rotate(angle);
      shape->move({ elementVector.x + compositeCenter.x, elementVector.y + compositeCenter.y });
      shape->rotate(angle);
  });
}

kerimov::Matrix kerimov::CompositeShape::split() const
{
  Matrix matrix;
  for_each(shapes_.get(), shapes_.get() + size_, [&matrix] (const element_type & shape) {
    matrix.add(shape);
  });
  return matrix;
}

void kerimov::CompositeShape::add(const element_type & shape)
{
  if (!shape) {
    throw std::invalid_argument("Shape added into CompositeShape must be not nullptr");
  }
  std::unique_ptr< element_type[] > newShapes(std::make_unique< element_type[] >(size_ + 1));
  std::swap_ranges(shapes_.get(), shapes_.get() + size_, newShapes.get());
  newShapes[size_++] = shape;
  shapes_ = std::move(newShapes);
}

void kerimov::CompositeShape::remove(size_t index)
{
  validateIndex(index);
  std::unique_ptr< element_type[] > newShapes(std::make_unique< element_type[] >(--size_));
  std::swap_ranges(shapes_.get(), shapes_.get() + index, newShapes.get());
  std::swap_ranges(shapes_.get() + index + 1, shapes_.get() + size_ + 1, newShapes.get() + index);
  shapes_ = std::move(newShapes);
}

size_t kerimov::CompositeShape::getSize() const noexcept
{
  return size_;
}

void kerimov::CompositeShape::clear() noexcept
{
  shapes_.reset();
  size_ = 0;
}

void kerimov::CompositeShape::validateIndex(size_t index) const
{
  if (index >= size_) {
    throw std::out_of_range("The index is larger than the elements in kerimov::CompositeShape.");
  }
}
