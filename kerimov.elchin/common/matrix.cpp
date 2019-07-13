#include "matrix.hpp"
#include <algorithm>
#include <stdexcept>

kerimov::Matrix::Matrix() noexcept:
  shapes_(),
  layers_(0),
  layerSize_(0)
{}

kerimov::Matrix::Matrix(kerimov::Matrix & rhs):
  shapes_(std::make_unique< element_type[] >(rhs.layers_ * rhs.layerSize_)),
  layers_(rhs.layers_),
  layerSize_(rhs.layerSize_)
{
  std::copy(rhs.shapes_.get(), rhs.shapes_.get() + layers_ * layerSize_, shapes_.get());
}

kerimov::Matrix::Matrix(kerimov::Matrix && rhs) noexcept:
  shapes_(std::move(rhs.shapes_)),
  layers_(rhs.layers_),
  layerSize_(rhs.layerSize_)
{
  rhs.layers_ = 0;
  rhs.layerSize_ = 0;
}

kerimov::Matrix & kerimov::Matrix::operator= (const kerimov::Matrix & rhs)
{
  if (this == &rhs) {
    return *this;
  }
  shapes_ = std::make_unique< element_type[] >(rhs.layers_ * rhs.layerSize_);
  layers_ = rhs.layers_;
  layerSize_ = rhs.layerSize_;
  std::copy(rhs.shapes_.get(), rhs.shapes_.get() + layers_ * layerSize_, shapes_.get());
  return *this;
}

kerimov::Matrix & kerimov::Matrix::operator= (kerimov::Matrix && rhs) noexcept
{
  shapes_ = std::move(rhs.shapes_);
  layers_ = rhs.layers_;
  layerSize_ = rhs.layerSize_;
  rhs.layers_ = 0;
  rhs.layerSize_ = 0;
  return *this;
}

kerimov::Matrix::layer_type kerimov::Matrix::operator[] (size_t index) const
{
  if (index >= layers_) {
    throw std::out_of_range("Index bigger than layers in kerimov::Matrix");
  }
  layer_type layer = std::make_unique< element_type[] >(layerSize_);
  std::copy(shapes_.get() + index * layerSize_, shapes_.get() + (index + 1) * layerSize_, layer.get());
  return layer;
}

void kerimov::Matrix::add(const element_type & shape)
{
  if (!shape) {
    throw std::invalid_argument("Shape added into Matrix must be not nullptr");
  }
  if ((layers_ == 0) && (layerSize_ == 0)) {
    shapes_ = std::make_unique< element_type[] >(1);
    layers_ = layerSize_ = 1;
    shapes_[0] = shape;
    return;
  }
  size_t i = 0;
  for (; i < layers_; ++i) {
    size_t j = 0;
    for(; j < layerSize_; ++j) {
      if (!shapes_[i * layerSize_ + j]) {
        shapes_[i * layerSize_ + j] = shape;
        return;
      }
      if (intersect(shapes_[i * layerSize_ + j], shape)) {
        break;
      }
    }
    if (j == layerSize_) {
      layer_type newShapes = std::make_unique< element_type[] >(layers_ * (layerSize_ + 1));
      for (size_t k = 0; k < layers_; ++k) {
        for (j = 0; j < layerSize_; ++j) {
          newShapes[k * layerSize_ + j + k] = shapes_[k * layerSize_ + j];
        }
      }
      ++layerSize_;
      newShapes[(i + 1) * layerSize_ - 1] = shape;
      shapes_ = std::move(newShapes);
      return;
    }
  }
  if (i == layers_) {
    layer_type newShapes = std::make_unique< element_type[] >((layers_ + 1) * layerSize_);
    for (size_t k = 0; k < layers_ * layerSize_; ++k) {
      newShapes[k] = shapes_[k];
    }
    newShapes[layers_ * layerSize_] = shape;
    ++layers_;
    shapes_ = std::move(newShapes);
  }
}

void kerimov::Matrix::clear() noexcept
{
  shapes_.reset();
  layers_ = 0;
  layerSize_ = 0;
}

size_t kerimov::Matrix::getLayers() const noexcept
{
  return layers_;
}

size_t kerimov::Matrix::getLayerSize() const noexcept
{
  return layerSize_;
}

bool kerimov::Matrix::intersect(const element_type & lhs, const element_type & rhs) noexcept
{
  return lhs->getFrameRect().intersect(rhs->getFrameRect());
}
